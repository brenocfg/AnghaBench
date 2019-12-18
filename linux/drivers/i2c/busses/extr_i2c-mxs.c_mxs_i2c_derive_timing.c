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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct mxs_i2c_dev {int timing0; int timing1; int timing2; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int) ; 
 int DIV_ROUND_UP (int const,int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int const,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int,int,int const,int const) ; 

__attribute__((used)) static void mxs_i2c_derive_timing(struct mxs_i2c_dev *i2c, uint32_t speed)
{
	/* The I2C block clock runs at 24MHz */
	const uint32_t clk = 24000000;
	uint32_t divider;
	uint16_t high_count, low_count, rcv_count, xmit_count;
	uint32_t bus_free, leadin;
	struct device *dev = i2c->dev;

	divider = DIV_ROUND_UP(clk, speed);

	if (divider < 25) {
		/*
		 * limit the divider, so that min(low_count, high_count)
		 * is >= 1
		 */
		divider = 25;
		dev_warn(dev,
			"Speed too high (%u.%03u kHz), using %u.%03u kHz\n",
			speed / 1000, speed % 1000,
			clk / divider / 1000, clk / divider % 1000);
	} else if (divider > 1897) {
		/*
		 * limit the divider, so that max(low_count, high_count)
		 * cannot exceed 1023
		 */
		divider = 1897;
		dev_warn(dev,
			"Speed too low (%u.%03u kHz), using %u.%03u kHz\n",
			speed / 1000, speed % 1000,
			clk / divider / 1000, clk / divider % 1000);
	}

	/*
	 * The I2C spec specifies the following timing data:
	 *                          standard mode  fast mode Bitfield name
	 * tLOW (SCL LOW period)     4700 ns        1300 ns
	 * tHIGH (SCL HIGH period)   4000 ns         600 ns
	 * tSU;DAT (data setup time)  250 ns         100 ns
	 * tHD;STA (START hold time) 4000 ns         600 ns
	 * tBUF (bus free time)      4700 ns        1300 ns
	 *
	 * The hardware (of the i.MX28 at least) seems to add 2 additional
	 * clock cycles to the low_count and 7 cycles to the high_count.
	 * This is compensated for by subtracting the respective constants
	 * from the values written to the timing registers.
	 */
	if (speed > 100000) {
		/* fast mode */
		low_count = DIV_ROUND_CLOSEST(divider * 13, (13 + 6));
		high_count = DIV_ROUND_CLOSEST(divider * 6, (13 + 6));
		leadin = DIV_ROUND_UP(600 * (clk / 1000000), 1000);
		bus_free = DIV_ROUND_UP(1300 * (clk / 1000000), 1000);
	} else {
		/* normal mode */
		low_count = DIV_ROUND_CLOSEST(divider * 47, (47 + 40));
		high_count = DIV_ROUND_CLOSEST(divider * 40, (47 + 40));
		leadin = DIV_ROUND_UP(4700 * (clk / 1000000), 1000);
		bus_free = DIV_ROUND_UP(4700 * (clk / 1000000), 1000);
	}
	rcv_count = high_count * 3 / 8;
	xmit_count = low_count * 3 / 8;

	dev_dbg(dev,
		"speed=%u(actual %u) divider=%u low=%u high=%u xmit=%u rcv=%u leadin=%u bus_free=%u\n",
		speed, clk / divider, divider, low_count, high_count,
		xmit_count, rcv_count, leadin, bus_free);

	low_count -= 2;
	high_count -= 7;
	i2c->timing0 = (high_count << 16) | rcv_count;
	i2c->timing1 = (low_count << 16) | xmit_count;
	i2c->timing2 = (bus_free << 16 | leadin);
}