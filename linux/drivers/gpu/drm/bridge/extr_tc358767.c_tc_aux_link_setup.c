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
struct tc_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int AUX_RX_FILTER_EN ; 
 int BGREN ; 
 int /*<<< orphan*/  DP0_AUXCFG1 ; 
 int /*<<< orphan*/  DP0_PLLCTRL ; 
 int /*<<< orphan*/  DP1_PLLCTRL ; 
 int /*<<< orphan*/  DP_PHY_CTRL ; 
 int ETIMEDOUT ; 
 int PHY_A0_EN ; 
 int /*<<< orphan*/  PHY_RDY ; 
 int PWR_SW_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tc_pllupdate (struct tc_data*,int /*<<< orphan*/ ) ; 
 int tc_poll_timeout (struct tc_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int tc_set_syspllparam (struct tc_data*) ; 

__attribute__((used)) static int tc_aux_link_setup(struct tc_data *tc)
{
	int ret;
	u32 dp0_auxcfg1;

	/* Setup DP-PHY / PLL */
	ret = tc_set_syspllparam(tc);
	if (ret)
		goto err;

	ret = regmap_write(tc->regmap, DP_PHY_CTRL,
			   BGREN | PWR_SW_EN | PHY_A0_EN);
	if (ret)
		goto err;
	/*
	 * Initially PLLs are in bypass. Force PLL parameter update,
	 * disable PLL bypass, enable PLL
	 */
	ret = tc_pllupdate(tc, DP0_PLLCTRL);
	if (ret)
		goto err;

	ret = tc_pllupdate(tc, DP1_PLLCTRL);
	if (ret)
		goto err;

	ret = tc_poll_timeout(tc, DP_PHY_CTRL, PHY_RDY, PHY_RDY, 1, 1000);
	if (ret == -ETIMEDOUT) {
		dev_err(tc->dev, "Timeout waiting for PHY to become ready");
		return ret;
	} else if (ret) {
		goto err;
	}

	/* Setup AUX link */
	dp0_auxcfg1  = AUX_RX_FILTER_EN;
	dp0_auxcfg1 |= 0x06 << 8; /* Aux Bit Period Calculator Threshold */
	dp0_auxcfg1 |= 0x3f << 0; /* Aux Response Timeout Timer */

	ret = regmap_write(tc->regmap, DP0_AUXCFG1, dp0_auxcfg1);
	if (ret)
		goto err;

	return 0;
err:
	dev_err(tc->dev, "tc_aux_link_setup failed: %d\n", ret);
	return ret;
}