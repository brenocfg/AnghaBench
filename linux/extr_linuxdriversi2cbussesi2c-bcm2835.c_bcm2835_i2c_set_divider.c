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
typedef  int u32 ;
struct bcm2835_i2c_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_clk_rate; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int BCM2835_I2C_CDIV_MAX ; 
 int BCM2835_I2C_CDIV_MIN ; 
 int /*<<< orphan*/  BCM2835_I2C_DEL ; 
 int /*<<< orphan*/  BCM2835_I2C_DIV ; 
 int BCM2835_I2C_FEDL_SHIFT ; 
 int BCM2835_I2C_REDL_SHIFT ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  bcm2835_i2c_writel (struct bcm2835_i2c_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int max (int,unsigned int) ; 

__attribute__((used)) static int bcm2835_i2c_set_divider(struct bcm2835_i2c_dev *i2c_dev)
{
	u32 divider, redl, fedl;

	divider = DIV_ROUND_UP(clk_get_rate(i2c_dev->clk),
			       i2c_dev->bus_clk_rate);
	/*
	 * Per the datasheet, the register is always interpreted as an even
	 * number, by rounding down. In other words, the LSB is ignored. So,
	 * if the LSB is set, increment the divider to avoid any issue.
	 */
	if (divider & 1)
		divider++;
	if ((divider < BCM2835_I2C_CDIV_MIN) ||
	    (divider > BCM2835_I2C_CDIV_MAX)) {
		dev_err_ratelimited(i2c_dev->dev, "Invalid clock-frequency\n");
		return -EINVAL;
	}

	bcm2835_i2c_writel(i2c_dev, BCM2835_I2C_DIV, divider);

	/*
	 * Number of core clocks to wait after falling edge before
	 * outputting the next data bit.  Note that both FEDL and REDL
	 * can't be greater than CDIV/2.
	 */
	fedl = max(divider / 16, 1u);

	/*
	 * Number of core clocks to wait after rising edge before
	 * sampling the next incoming data bit.
	 */
	redl = max(divider / 4, 1u);

	bcm2835_i2c_writel(i2c_dev, BCM2835_I2C_DEL,
			   (fedl << BCM2835_I2C_FEDL_SHIFT) |
			   (redl << BCM2835_I2C_REDL_SHIFT));
	return 0;
}