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
struct imx_i2c_struct {unsigned int cur_clk; unsigned int bitrate; unsigned int disable_delay; int /*<<< orphan*/  ifdr; TYPE_1__* hwdata; } ;
struct imx_i2c_clk_pair {unsigned int div; int /*<<< orphan*/  val; } ;
struct TYPE_2__ {int ndivs; struct imx_i2c_clk_pair* clk_div; } ;

/* Variables and functions */

__attribute__((used)) static void i2c_imx_set_clk(struct imx_i2c_struct *i2c_imx,
			    unsigned int i2c_clk_rate)
{
	struct imx_i2c_clk_pair *i2c_clk_div = i2c_imx->hwdata->clk_div;
	unsigned int div;
	int i;

	/* Divider value calculation */
	if (i2c_imx->cur_clk == i2c_clk_rate)
		return;

	i2c_imx->cur_clk = i2c_clk_rate;

	div = (i2c_clk_rate + i2c_imx->bitrate - 1) / i2c_imx->bitrate;
	if (div < i2c_clk_div[0].div)
		i = 0;
	else if (div > i2c_clk_div[i2c_imx->hwdata->ndivs - 1].div)
		i = i2c_imx->hwdata->ndivs - 1;
	else
		for (i = 0; i2c_clk_div[i].div < div; i++)
			;

	/* Store divider value */
	i2c_imx->ifdr = i2c_clk_div[i].val;

	/*
	 * There dummy delay is calculated.
	 * It should be about one I2C clock period long.
	 * This delay is used in I2C bus disable function
	 * to fix chip hardware bug.
	 */
	i2c_imx->disable_delay = (500000U * i2c_clk_div[i].div
		+ (i2c_clk_rate / 2) - 1) / (i2c_clk_rate / 2);

#ifdef CONFIG_I2C_DEBUG_BUS
	dev_dbg(&i2c_imx->adapter.dev, "I2C_CLK=%d, REQ DIV=%d\n",
		i2c_clk_rate, div);
	dev_dbg(&i2c_imx->adapter.dev, "IFDR[IC]=0x%x, REAL DIV=%d\n",
		i2c_clk_div[i].val, i2c_clk_div[i].div);
#endif
}