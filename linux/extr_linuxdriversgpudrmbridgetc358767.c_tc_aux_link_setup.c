#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int num_lanes; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct tc_data {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; TYPE_2__ link; int /*<<< orphan*/  refclk; } ;

/* Variables and functions */
 int AUX_RX_FILTER_EN ; 
 int BGREN ; 
 int /*<<< orphan*/  DP0_AUXCFG1 ; 
 int /*<<< orphan*/  DP0_PLLCTRL ; 
 int /*<<< orphan*/  DP1_PLLCTRL ; 
 int /*<<< orphan*/  DP_PHY_CTRL ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int LSCLK_DIV_2 ; 
 int PHY_2LANE ; 
 int PHY_A0_EN ; 
 int /*<<< orphan*/  PHY_RDY ; 
 int PLLEN ; 
 int PLLUPDATE ; 
 int PWR_SW_EN ; 
 int REF_FREQ_13M ; 
 int REF_FREQ_19M2 ; 
 int REF_FREQ_26M ; 
 int REF_FREQ_38M4 ; 
 int SYSCLK_SEL_LSCLK ; 
 int /*<<< orphan*/  SYS_PLLPARAM ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int tc_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  tc_wait_pll_lock (struct tc_data*) ; 
 int /*<<< orphan*/  tc_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tc_aux_link_setup(struct tc_data *tc)
{
	unsigned long rate;
	u32 value;
	int ret;
	u32 dp_phy_ctrl;

	rate = clk_get_rate(tc->refclk);
	switch (rate) {
	case 38400000:
		value = REF_FREQ_38M4;
		break;
	case 26000000:
		value = REF_FREQ_26M;
		break;
	case 19200000:
		value = REF_FREQ_19M2;
		break;
	case 13000000:
		value = REF_FREQ_13M;
		break;
	default:
		dev_err(tc->dev, "Invalid refclk rate: %lu Hz\n", rate);
		return -EINVAL;
	}

	/* Setup DP-PHY / PLL */
	value |= SYSCLK_SEL_LSCLK | LSCLK_DIV_2;
	tc_write(SYS_PLLPARAM, value);

	dp_phy_ctrl = BGREN | PWR_SW_EN | PHY_A0_EN;
	if (tc->link.base.num_lanes == 2)
		dp_phy_ctrl |= PHY_2LANE;
	tc_write(DP_PHY_CTRL, dp_phy_ctrl);

	/*
	 * Initially PLLs are in bypass. Force PLL parameter update,
	 * disable PLL bypass, enable PLL
	 */
	tc_write(DP0_PLLCTRL, PLLUPDATE | PLLEN);
	tc_wait_pll_lock(tc);

	tc_write(DP1_PLLCTRL, PLLUPDATE | PLLEN);
	tc_wait_pll_lock(tc);

	ret = tc_poll_timeout(tc->regmap, DP_PHY_CTRL, PHY_RDY, PHY_RDY, 1,
			      1000);
	if (ret == -ETIMEDOUT) {
		dev_err(tc->dev, "Timeout waiting for PHY to become ready");
		return ret;
	} else if (ret)
		goto err;

	/* Setup AUX link */
	tc_write(DP0_AUXCFG1, AUX_RX_FILTER_EN |
		 (0x06 << 8) |	/* Aux Bit Period Calculator Threshold */
		 (0x3f << 0));	/* Aux Response Timeout Timer */

	return 0;
err:
	dev_err(tc->dev, "tc_aux_link_setup failed: %d\n", ret);
	return ret;
}