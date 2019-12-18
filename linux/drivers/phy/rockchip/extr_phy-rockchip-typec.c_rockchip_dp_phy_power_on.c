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
struct rockchip_usb3phy_port_cfg {int /*<<< orphan*/  uphy_dp_sel; } ;
struct rockchip_typec_phy {int mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; scalar_t__ base; struct rockchip_usb3phy_port_cfg* port_cfgs; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int DP_MODE_A0 ; 
 int DP_MODE_A2 ; 
 scalar_t__ DP_MODE_CTL ; 
 int /*<<< orphan*/  DP_MODE_ENTER_A0 ; 
 int /*<<< orphan*/  DP_MODE_ENTER_A2 ; 
 int ENODEV ; 
 int MODE_DFP_DP ; 
 int MODE_DISCONNECT ; 
 int /*<<< orphan*/  PHY_MODE_SET_TIMEOUT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rockchip_typec_phy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  property_enable (struct rockchip_typec_phy*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  readl ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,scalar_t__,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcphy_dp_aux_calibration (struct rockchip_typec_phy*) ; 
 int tcphy_get_mode (struct rockchip_typec_phy*) ; 
 int /*<<< orphan*/  tcphy_phy_deinit (struct rockchip_typec_phy*) ; 
 int tcphy_phy_init (struct rockchip_typec_phy*,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rockchip_dp_phy_power_on(struct phy *phy)
{
	struct rockchip_typec_phy *tcphy = phy_get_drvdata(phy);
	const struct rockchip_usb3phy_port_cfg *cfg = tcphy->port_cfgs;
	int new_mode, ret = 0;
	u32 val;

	mutex_lock(&tcphy->lock);

	new_mode = tcphy_get_mode(tcphy);
	if (new_mode < 0) {
		ret = new_mode;
		goto unlock_ret;
	}

	if (!(new_mode & MODE_DFP_DP)) {
		ret = -ENODEV;
		goto unlock_ret;
	}

	if (tcphy->mode == new_mode)
		goto unlock_ret;

	/*
	 * If the PHY has been power on, but the mode is not DP only mode,
	 * re-init the PHY for setting all of 4 lanes to DP.
	 */
	if (new_mode == MODE_DFP_DP && tcphy->mode != MODE_DISCONNECT) {
		tcphy_phy_deinit(tcphy);
		ret = tcphy_phy_init(tcphy, new_mode);
	} else if (tcphy->mode == MODE_DISCONNECT) {
		ret = tcphy_phy_init(tcphy, new_mode);
	}
	if (ret)
		goto unlock_ret;

	property_enable(tcphy, &cfg->uphy_dp_sel, 1);

	ret = readx_poll_timeout(readl, tcphy->base + DP_MODE_CTL,
				 val, val & DP_MODE_A2, 1000,
				 PHY_MODE_SET_TIMEOUT);
	if (ret < 0) {
		dev_err(tcphy->dev, "failed to wait TCPHY enter A2\n");
		goto power_on_finish;
	}

	tcphy_dp_aux_calibration(tcphy);

	writel(DP_MODE_ENTER_A0, tcphy->base + DP_MODE_CTL);

	ret = readx_poll_timeout(readl, tcphy->base + DP_MODE_CTL,
				 val, val & DP_MODE_A0, 1000,
				 PHY_MODE_SET_TIMEOUT);
	if (ret < 0) {
		writel(DP_MODE_ENTER_A2, tcphy->base + DP_MODE_CTL);
		dev_err(tcphy->dev, "failed to wait TCPHY enter A0\n");
		goto power_on_finish;
	}

	tcphy->mode |= MODE_DFP_DP;

power_on_finish:
	if (tcphy->mode == MODE_DISCONNECT)
		tcphy_phy_deinit(tcphy);
unlock_ret:
	mutex_unlock(&tcphy->lock);
	return ret;
}