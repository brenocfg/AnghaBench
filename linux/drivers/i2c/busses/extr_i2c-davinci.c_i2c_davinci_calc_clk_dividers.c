#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct device_node {int dummy; } ;
struct davinci_i2c_platform_data {int bus_freq; } ;
struct davinci_i2c_dev {TYPE_1__* dev; int /*<<< orphan*/  clk; struct davinci_i2c_platform_data* pdata; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAVINCI_I2C_CLKH_REG ; 
 int /*<<< orphan*/  DAVINCI_I2C_CLKL_REG ; 
 int /*<<< orphan*/  DAVINCI_I2C_PSC_REG ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  davinci_i2c_write_reg (struct davinci_i2c_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int,int) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 

__attribute__((used)) static void i2c_davinci_calc_clk_dividers(struct davinci_i2c_dev *dev)
{
	struct davinci_i2c_platform_data *pdata = dev->pdata;
	u16 psc;
	u32 clk;
	u32 d;
	u32 clkh;
	u32 clkl;
	u32 input_clock = clk_get_rate(dev->clk);
	struct device_node *of_node = dev->dev->of_node;

	/* NOTE: I2C Clock divider programming info
	 * As per I2C specs the following formulas provide prescaler
	 * and low/high divider values
	 * input clk --> PSC Div -----------> ICCL/H Div --> output clock
	 *                       module clk
	 *
	 * output clk = module clk / (PSC + 1) [ (ICCL + d) + (ICCH + d) ]
	 *
	 * Thus,
	 * (ICCL + ICCH) = clk = (input clk / ((psc +1) * output clk)) - 2d;
	 *
	 * where if PSC == 0, d = 7,
	 *       if PSC == 1, d = 6
	 *       if PSC > 1 , d = 5
	 *
	 * Note:
	 * d is always 6 on Keystone I2C controller
	 */

	/*
	 * Both Davinci and current Keystone User Guides recommend a value
	 * between 7MHz and 12MHz. In reality 7MHz module clock doesn't
	 * always produce enough margin between SDA and SCL transitions.
	 * Measurements show that the higher the module clock is, the
	 * bigger is the margin, providing more reliable communication.
	 * So we better target for 12MHz.
	 */
	psc = (input_clock / 12000000) - 1;
	if ((input_clock / (psc + 1)) > 12000000)
		psc++;	/* better to run under spec than over */
	d = (psc >= 2) ? 5 : 7 - psc;

	if (of_node && of_device_is_compatible(of_node, "ti,keystone-i2c"))
		d = 6;

	clk = ((input_clock / (psc + 1)) / (pdata->bus_freq * 1000));
	/* Avoid driving the bus too fast because of rounding errors above */
	if (input_clock / (psc + 1) / clk > pdata->bus_freq * 1000)
		clk++;
	/*
	 * According to I2C-BUS Spec 2.1, in FAST-MODE LOW period should be at
	 * least 1.3uS, which is not the case with 50% duty cycle. Driving HIGH
	 * to LOW ratio as 1 to 2 is more safe.
	 */
	if (pdata->bus_freq > 100)
		clkl = (clk << 1) / 3;
	else
		clkl = (clk >> 1);
	/*
	 * It's not always possible to have 1 to 2 ratio when d=7, so fall back
	 * to minimal possible clkh in this case.
	 *
	 * Note:
	 * CLKH is not allowed to be 0, in this case I2C clock is not generated
	 * at all
	 */
	if (clk > clkl + d) {
		clkh = clk - clkl - d;
		clkl -= d;
	} else {
		clkh = 1;
		clkl = clk - (d << 1);
	}

	davinci_i2c_write_reg(dev, DAVINCI_I2C_PSC_REG, psc);
	davinci_i2c_write_reg(dev, DAVINCI_I2C_CLKH_REG, clkh);
	davinci_i2c_write_reg(dev, DAVINCI_I2C_CLKL_REG, clkl);

	dev_dbg(dev->dev, "input_clock = %d, CLK = %d\n", input_clock, clk);
}