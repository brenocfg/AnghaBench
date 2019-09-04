#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_6__ {int rate; int num_lanes; } ;
struct TYPE_4__ {scalar_t__ assr; int scrambler_dis; TYPE_3__ base; scalar_t__ coding8b10b; scalar_t__ spread; } ;
struct drm_dp_aux {int dummy; } ;
struct tc_data {scalar_t__ assr; struct device* dev; TYPE_2__* mode; TYPE_1__ link; int /*<<< orphan*/  regmap; int /*<<< orphan*/  refclk; struct drm_dp_aux aux; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int clock; } ;

/* Variables and functions */
 int BGREN ; 
 int /*<<< orphan*/  BPC_8 ; 
 int /*<<< orphan*/  DP0_MISC ; 
 int /*<<< orphan*/  DP0_PLLCTRL ; 
 int /*<<< orphan*/  DP0_SRCCTRL ; 
 int DP0_SRCCTRL_AUTOCORRECT ; 
 int DP0_SRCCTRL_BW27 ; 
 int DP0_SRCCTRL_SSCG ; 
 int /*<<< orphan*/  DP1_PLLCTRL ; 
 int /*<<< orphan*/  DP1_SRCCTRL ; 
 int /*<<< orphan*/  DP_DOWNSPREAD_CTRL ; 
 int /*<<< orphan*/  DP_EDP_CONFIGURATION_SET ; 
 int DP_LINK_SCRAMBLING_DISABLE ; 
 int /*<<< orphan*/  DP_PHY_CTRL ; 
 int DP_PHY_RST ; 
 int DP_SET_ANSI_8B10B ; 
 int /*<<< orphan*/  DP_SINK_COUNT ; 
 int DP_SPREAD_AMP_0_5 ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_1 ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_2 ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_SET ; 
 int EAGAIN ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int LSCLK_DIV_2 ; 
 int PHY_2LANE ; 
 int PHY_A0_EN ; 
 int PHY_M0_EN ; 
 int PHY_M0_RST ; 
 int PHY_M1_RST ; 
 int PHY_RDY ; 
 int PLLEN ; 
 int PLLUPDATE ; 
 int PWR_SW_EN ; 
 int REF_FREQ_13M ; 
 int REF_FREQ_19M2 ; 
 int REF_FREQ_26M ; 
 int REF_FREQ_38M4 ; 
 int SYSCLK_SEL_LSCLK ; 
 int /*<<< orphan*/  SYS_PLLPARAM ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int) ; 
 int /*<<< orphan*/  drm_dp_channel_eq_ok (int*,int) ; 
 int drm_dp_dpcd_read (struct drm_dp_aux*,int /*<<< orphan*/ ,int*,int) ; 
 int drm_dp_dpcd_read_link_status (struct drm_dp_aux*,int*) ; 
 int drm_dp_dpcd_readb (struct drm_dp_aux*,int /*<<< orphan*/ ,int*) ; 
 int drm_dp_dpcd_write (struct drm_dp_aux*,int /*<<< orphan*/ ,int*,int) ; 
 int drm_dp_dpcd_writeb (struct drm_dp_aux*,int /*<<< orphan*/ ,int) ; 
 int drm_dp_link_configure (struct drm_dp_aux*,TYPE_3__*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tc_link_training (struct tc_data*,int /*<<< orphan*/ ) ; 
 int tc_pxl_pll_en (struct tc_data*,unsigned int,int) ; 
 int /*<<< orphan*/  tc_read (int /*<<< orphan*/ ,int*) ; 
 int tc_set_video_mode (struct tc_data*,TYPE_2__*) ; 
 int tc_srcctrl (struct tc_data*) ; 
 int tc_stream_clock_calc (struct tc_data*) ; 
 scalar_t__ tc_test_pattern ; 
 int /*<<< orphan*/  tc_wait_pll_lock (struct tc_data*) ; 
 int /*<<< orphan*/  tc_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tc_main_link_setup(struct tc_data *tc)
{
	struct drm_dp_aux *aux = &tc->aux;
	struct device *dev = tc->dev;
	unsigned int rate;
	u32 dp_phy_ctrl;
	int timeout;
	u32 value;
	int ret;
	u8 tmp[8];

	/* display mode should be set at this point */
	if (!tc->mode)
		return -EINVAL;

	tc_write(DP0_SRCCTRL, tc_srcctrl(tc));
	/* SSCG and BW27 on DP1 must be set to the same as on DP0 */
	tc_write(DP1_SRCCTRL,
		 (tc->link.spread ? DP0_SRCCTRL_SSCG : 0) |
		 ((tc->link.base.rate != 162000) ? DP0_SRCCTRL_BW27 : 0));

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
		return -EINVAL;
	}
	value |= SYSCLK_SEL_LSCLK | LSCLK_DIV_2;
	tc_write(SYS_PLLPARAM, value);

	/* Setup Main Link */
	dp_phy_ctrl = BGREN | PWR_SW_EN | PHY_A0_EN | PHY_M0_EN;
	if (tc->link.base.num_lanes == 2)
		dp_phy_ctrl |= PHY_2LANE;
	tc_write(DP_PHY_CTRL, dp_phy_ctrl);
	msleep(100);

	/* PLL setup */
	tc_write(DP0_PLLCTRL, PLLUPDATE | PLLEN);
	tc_wait_pll_lock(tc);

	tc_write(DP1_PLLCTRL, PLLUPDATE | PLLEN);
	tc_wait_pll_lock(tc);

	/* PXL PLL setup */
	if (tc_test_pattern) {
		ret = tc_pxl_pll_en(tc, clk_get_rate(tc->refclk),
				    1000 * tc->mode->clock);
		if (ret)
			goto err;
	}

	/* Reset/Enable Main Links */
	dp_phy_ctrl |= DP_PHY_RST | PHY_M1_RST | PHY_M0_RST;
	tc_write(DP_PHY_CTRL, dp_phy_ctrl);
	usleep_range(100, 200);
	dp_phy_ctrl &= ~(DP_PHY_RST | PHY_M1_RST | PHY_M0_RST);
	tc_write(DP_PHY_CTRL, dp_phy_ctrl);

	timeout = 1000;
	do {
		tc_read(DP_PHY_CTRL, &value);
		udelay(1);
	} while ((!(value & PHY_RDY)) && (--timeout));

	if (timeout == 0) {
		dev_err(dev, "timeout waiting for phy become ready");
		return -ETIMEDOUT;
	}

	/* Set misc: 8 bits per color */
	ret = regmap_update_bits(tc->regmap, DP0_MISC, BPC_8, BPC_8);
	if (ret)
		goto err;

	/*
	 * ASSR mode
	 * on TC358767 side ASSR configured through strap pin
	 * seems there is no way to change this setting from SW
	 *
	 * check is tc configured for same mode
	 */
	if (tc->assr != tc->link.assr) {
		dev_dbg(dev, "Trying to set display to ASSR: %d\n",
			tc->assr);
		/* try to set ASSR on display side */
		tmp[0] = tc->assr;
		ret = drm_dp_dpcd_writeb(aux, DP_EDP_CONFIGURATION_SET, tmp[0]);
		if (ret < 0)
			goto err_dpcd_read;
		/* read back */
		ret = drm_dp_dpcd_readb(aux, DP_EDP_CONFIGURATION_SET, tmp);
		if (ret < 0)
			goto err_dpcd_read;

		if (tmp[0] != tc->assr) {
			dev_dbg(dev, "Failed to switch display ASSR to %d, falling back to unscrambled mode\n",
				 tc->assr);
			/* trying with disabled scrambler */
			tc->link.scrambler_dis = 1;
		}
	}

	/* Setup Link & DPRx Config for Training */
	ret = drm_dp_link_configure(aux, &tc->link.base);
	if (ret < 0)
		goto err_dpcd_write;

	/* DOWNSPREAD_CTRL */
	tmp[0] = tc->link.spread ? DP_SPREAD_AMP_0_5 : 0x00;
	/* MAIN_LINK_CHANNEL_CODING_SET */
	tmp[1] =  tc->link.coding8b10b ? DP_SET_ANSI_8B10B : 0x00;
	ret = drm_dp_dpcd_write(aux, DP_DOWNSPREAD_CTRL, tmp, 2);
	if (ret < 0)
		goto err_dpcd_write;

	ret = tc_link_training(tc, DP_TRAINING_PATTERN_1);
	if (ret)
		goto err;

	ret = tc_link_training(tc, DP_TRAINING_PATTERN_2);
	if (ret)
		goto err;

	/* Clear DPCD 0x102 */
	/* Note: Can Not use DP0_SNKLTCTRL (0x06E4) short cut */
	tmp[0] = tc->link.scrambler_dis ? DP_LINK_SCRAMBLING_DISABLE : 0x00;
	ret = drm_dp_dpcd_writeb(aux, DP_TRAINING_PATTERN_SET, tmp[0]);
	if (ret < 0)
		goto err_dpcd_write;

	/* Clear Training Pattern, set AutoCorrect Mode = 1 */
	tc_write(DP0_SRCCTRL, tc_srcctrl(tc) | DP0_SRCCTRL_AUTOCORRECT);

	/* Wait */
	timeout = 100;
	do {
		udelay(1);
		/* Read DPCD 0x202-0x207 */
		ret = drm_dp_dpcd_read_link_status(aux, tmp + 2);
		if (ret < 0)
			goto err_dpcd_read;
	} while ((--timeout) &&
		 !(drm_dp_channel_eq_ok(tmp + 2,  tc->link.base.num_lanes)));

	if (timeout == 0) {
		/* Read DPCD 0x200-0x201 */
		ret = drm_dp_dpcd_read(aux, DP_SINK_COUNT, tmp, 2);
		if (ret < 0)
			goto err_dpcd_read;
		dev_err(dev, "channel(s) EQ not ok\n");
		dev_info(dev, "0x0200 SINK_COUNT: 0x%02x\n", tmp[0]);
		dev_info(dev, "0x0201 DEVICE_SERVICE_IRQ_VECTOR: 0x%02x\n",
			 tmp[1]);
		dev_info(dev, "0x0202 LANE0_1_STATUS: 0x%02x\n", tmp[2]);
		dev_info(dev, "0x0204 LANE_ALIGN_STATUS_UPDATED: 0x%02x\n",
			 tmp[4]);
		dev_info(dev, "0x0205 SINK_STATUS: 0x%02x\n", tmp[5]);
		dev_info(dev, "0x0206 ADJUST_REQUEST_LANE0_1: 0x%02x\n",
			 tmp[6]);

		return -EAGAIN;
	}

	ret = tc_set_video_mode(tc, tc->mode);
	if (ret)
		goto err;

	/* Set M/N */
	ret = tc_stream_clock_calc(tc);
	if (ret)
		goto err;

	return 0;
err_dpcd_read:
	dev_err(tc->dev, "Failed to read DPCD: %d\n", ret);
	return ret;
err_dpcd_write:
	dev_err(tc->dev, "Failed to write DPCD: %d\n", ret);
err:
	return ret;
}