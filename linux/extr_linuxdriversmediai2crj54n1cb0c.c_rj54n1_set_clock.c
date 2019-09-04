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
struct TYPE_2__ {int ratio_tg; int ratio_t; int ratio_r; int ratio_op; int ratio_o; } ;
struct rj54n1 {TYPE_1__ clk_div; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int E_EXCLK ; 
 int PLL_L ; 
 int PLL_N ; 
 int /*<<< orphan*/  RJ54N1_CLK_RST ; 
 int /*<<< orphan*/  RJ54N1_OCLK_DSP ; 
 int /*<<< orphan*/  RJ54N1_OCLK_SEL_EN ; 
 int /*<<< orphan*/  RJ54N1_PLL_EN ; 
 int /*<<< orphan*/  RJ54N1_PLL_L ; 
 int /*<<< orphan*/  RJ54N1_PLL_N ; 
 int /*<<< orphan*/  RJ54N1_RAMP_TGCLK_EN ; 
 int /*<<< orphan*/  RJ54N1_RATIO_O ; 
 int /*<<< orphan*/  RJ54N1_RATIO_OP ; 
 int /*<<< orphan*/  RJ54N1_RATIO_R ; 
 int /*<<< orphan*/  RJ54N1_RATIO_T ; 
 int /*<<< orphan*/  RJ54N1_RATIO_TG ; 
 int /*<<< orphan*/  RJ54N1_RESET_STANDBY ; 
 int /*<<< orphan*/  RJ54N1_TG_BYPASS ; 
 int SEN_RSTX ; 
 int SOFT_STDBY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int reg_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int reg_set (struct i2c_client*,int /*<<< orphan*/ ,int,int) ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct rj54n1* to_rj54n1 (struct i2c_client*) ; 

__attribute__((used)) static int rj54n1_set_clock(struct i2c_client *client)
{
	struct rj54n1 *rj54n1 = to_rj54n1(client);
	int ret;

	/* Enable external clock */
	ret = reg_write(client, RJ54N1_RESET_STANDBY, E_EXCLK | SOFT_STDBY);
	/* Leave stand-by. Note: use this when implementing suspend / resume */
	if (!ret)
		ret = reg_write(client, RJ54N1_RESET_STANDBY, E_EXCLK);

	if (!ret)
		ret = reg_write(client, RJ54N1_PLL_L, PLL_L);
	if (!ret)
		ret = reg_write(client, RJ54N1_PLL_N, PLL_N);

	/* TGCLK dividers */
	if (!ret)
		ret = reg_write(client, RJ54N1_RATIO_TG,
				rj54n1->clk_div.ratio_tg);
	if (!ret)
		ret = reg_write(client, RJ54N1_RATIO_T,
				rj54n1->clk_div.ratio_t);
	if (!ret)
		ret = reg_write(client, RJ54N1_RATIO_R,
				rj54n1->clk_div.ratio_r);

	/* Enable TGCLK & RAMP */
	if (!ret)
		ret = reg_write(client, RJ54N1_RAMP_TGCLK_EN, 3);

	/* Disable clock output */
	if (!ret)
		ret = reg_write(client, RJ54N1_OCLK_DSP, 0);

	/* Set divisors */
	if (!ret)
		ret = reg_write(client, RJ54N1_RATIO_OP,
				rj54n1->clk_div.ratio_op);
	if (!ret)
		ret = reg_write(client, RJ54N1_RATIO_O,
				rj54n1->clk_div.ratio_o);

	/* Enable OCLK */
	if (!ret)
		ret = reg_write(client, RJ54N1_OCLK_SEL_EN, 1);

	/* Use PLL for Timing Generator, write 2 to reserved bits */
	if (!ret)
		ret = reg_write(client, RJ54N1_TG_BYPASS, 2);

	/* Take sensor out of reset */
	if (!ret)
		ret = reg_write(client, RJ54N1_RESET_STANDBY,
				E_EXCLK | SEN_RSTX);
	/* Enable PLL */
	if (!ret)
		ret = reg_write(client, RJ54N1_PLL_EN, 1);

	/* Wait for PLL to stabilise */
	msleep(10);

	/* Enable clock to frequency divider */
	if (!ret)
		ret = reg_write(client, RJ54N1_CLK_RST, 1);

	if (!ret)
		ret = reg_read(client, RJ54N1_CLK_RST);
	if (ret != 1) {
		dev_err(&client->dev,
			"Resetting RJ54N1CB0C clock failed: %d!\n", ret);
		return -EIO;
	}

	/* Start the PLL */
	ret = reg_set(client, RJ54N1_OCLK_DSP, 1, 1);

	/* Enable OCLK */
	if (!ret)
		ret = reg_write(client, RJ54N1_OCLK_SEL_EN, 1);

	return ret;
}