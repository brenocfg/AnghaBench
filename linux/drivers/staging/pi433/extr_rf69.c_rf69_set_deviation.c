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
typedef  int u64 ;
typedef  int u32 ;
struct spi_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int FDEVMASB_MASK ; 
 int F_OSC ; 
 int /*<<< orphan*/  REG_FDEV_LSB ; 
 int /*<<< orphan*/  REG_FDEV_MSB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int rf69_write_reg (struct spi_device*,int /*<<< orphan*/ ,int) ; 

int rf69_set_deviation(struct spi_device *spi, u32 deviation)
{
	int retval;
	u64 f_reg;
	u64 f_step;
	u8 msb;
	u8 lsb;
	u64 factor = 1000000; // to improve precision of calculation

	// TODO: Dependency to bitrate
	if (deviation < 600 || deviation > 500000) {
		dev_dbg(&spi->dev, "set_deviation: illegal input param");
		return -EINVAL;
	}

	// calculat f step
	f_step = F_OSC * factor;
	do_div(f_step, 524288); //  524288 = 2^19

	// calculate register settings
	f_reg = deviation * factor;
	do_div(f_reg, f_step);

	msb = (f_reg & 0xff00) >> 8;
	lsb = (f_reg & 0xff);

	// check msb
	if (msb & ~FDEVMASB_MASK) {
		dev_dbg(&spi->dev, "set_deviation: err in calc of msb");
		return -EINVAL;
	}

	// write to chip
	retval = rf69_write_reg(spi, REG_FDEV_MSB, msb);
	if (retval)
		return retval;
	retval = rf69_write_reg(spi, REG_FDEV_LSB, lsb);
	if (retval)
		return retval;

	return 0;
}