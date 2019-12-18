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
typedef  int u8 ;
typedef  int u16 ;
struct spi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_PREAMBLE_LSB ; 
 int /*<<< orphan*/  REG_PREAMBLE_MSB ; 
 int rf69_write_reg (struct spi_device*,int /*<<< orphan*/ ,int) ; 

int rf69_set_preamble_length(struct spi_device *spi, u16 preamble_length)
{
	int retval;
	u8 msb, lsb;

	/* no value check needed - u16 exactly matches register size */

	/* calculate reg settings */
	msb = (preamble_length & 0xff00) >> 8;
	lsb = (preamble_length & 0xff);

	/* transmit to chip */
	retval = rf69_write_reg(spi, REG_PREAMBLE_MSB, msb);
	if (retval)
		return retval;
	return rf69_write_reg(spi, REG_PREAMBLE_LSB, lsb);
}