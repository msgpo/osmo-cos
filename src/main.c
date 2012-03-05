#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "cc32/cc32_flcon.h"
#include "cc32/cc32_irq.h"
#include "cc32/iso7816_slave.h"

#define BASE_ISO7816_SLAVE	0x0F8800

const uint8_t atr[] = "ThisIsNotAnATR\n";

int main(int argc, char **argv)
{
	/* we generally don't want interrupts yet */
	cc32_irq_disable(IRQ_FLCON | IRQ_UART);
	char *atr2 = "12345";

	iso7816_slave_init();

	iso7816_slave_tx_ch('H');
	iso7816_slave_tx_ch('W');
	iso7816_slave_tx_ch('H');
	iso7816_slave_tx_ch('W');

	//iso7816_slave_tx(atr2, 5);

	iso7816_slave_tx_ch(atr2[0]);
	iso7816_slave_tx_ch(atr2[1]);
	iso7816_slave_tx_ch(atr2[2]);
	iso7816_slave_tx_ch(atr2[3]);
	iso7816_slave_tx_ch(atr2[4]);

	iso7816_slave_tx5(atr2);

	if (iso7816_slave_tx(atr, sizeof(atr)) < 0)
		cc32_flash_erase(10*256, 256);

	while (1) {
		//cc32_flash_erase(10*256, 256);
	}
}
