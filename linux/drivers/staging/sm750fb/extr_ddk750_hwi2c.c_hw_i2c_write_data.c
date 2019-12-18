#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ I2C_BYTE_COUNT ; 
 scalar_t__ I2C_CTRL ; 
 unsigned char I2C_CTRL_CTRL ; 
 scalar_t__ I2C_DATA0 ; 
 scalar_t__ I2C_RESET ; 
 scalar_t__ I2C_SLAVE_ADDRESS ; 
 unsigned int MAX_HWI2C_FIFO ; 
 scalar_t__ hw_i2c_wait_tx_done () ; 
 unsigned char peek32 (scalar_t__) ; 
 int /*<<< orphan*/  poke32 (scalar_t__,unsigned char) ; 

__attribute__((used)) static unsigned int hw_i2c_write_data(unsigned char addr,
				      unsigned int length,
				      unsigned char *buf)
{
	unsigned char count, i;
	unsigned int total_bytes = 0;

	/* Set the Device Address */
	poke32(I2C_SLAVE_ADDRESS, addr & ~0x01);

	/*
	 * Write data.
	 * Note:
	 *      Only 16 byte can be accessed per i2c start instruction.
	 */
	do {
		/*
		 * Reset I2C by writing 0 to I2C_RESET register to
		 * clear the previous status.
		 */
		poke32(I2C_RESET, 0);

		/* Set the number of bytes to be written */
		if (length < MAX_HWI2C_FIFO)
			count = length - 1;
		else
			count = MAX_HWI2C_FIFO - 1;
		poke32(I2C_BYTE_COUNT, count);

		/* Move the data to the I2C data register */
		for (i = 0; i <= count; i++)
			poke32(I2C_DATA0 + i, *buf++);

		/* Start the I2C */
		poke32(I2C_CTRL, peek32(I2C_CTRL) | I2C_CTRL_CTRL);

		/* Wait until the transfer is completed. */
		if (hw_i2c_wait_tx_done() != 0)
			break;

		/* Subtract length */
		length -= (count + 1);

		/* Total byte written */
		total_bytes += (count + 1);

	} while (length > 0);

	return total_bytes;
}