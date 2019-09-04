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
typedef  int u16 ;
struct dw_hdmi_phy_data {int gen; } ;
struct TYPE_2__ {struct dw_hdmi_phy_data* data; } ;
struct dw_hdmi {int /*<<< orphan*/  dev; TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDMI_PHY_STAT0 ; 
 int HDMI_PHY_TX_PHY_LOCK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dw_hdmi_phy_enable_powerdown (struct dw_hdmi*,int) ; 
 int /*<<< orphan*/  dw_hdmi_phy_enable_tmds (struct dw_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_hdmi_phy_gen2_pddq (struct dw_hdmi*,int) ; 
 int /*<<< orphan*/  dw_hdmi_phy_gen2_txpwron (struct dw_hdmi*,int /*<<< orphan*/ ) ; 
 int hdmi_readb (struct dw_hdmi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void dw_hdmi_phy_power_off(struct dw_hdmi *hdmi)
{
	const struct dw_hdmi_phy_data *phy = hdmi->phy.data;
	unsigned int i;
	u16 val;

	if (phy->gen == 1) {
		dw_hdmi_phy_enable_tmds(hdmi, 0);
		dw_hdmi_phy_enable_powerdown(hdmi, true);
		return;
	}

	dw_hdmi_phy_gen2_txpwron(hdmi, 0);

	/*
	 * Wait for TX_PHY_LOCK to be deasserted to indicate that the PHY went
	 * to low power mode.
	 */
	for (i = 0; i < 5; ++i) {
		val = hdmi_readb(hdmi, HDMI_PHY_STAT0);
		if (!(val & HDMI_PHY_TX_PHY_LOCK))
			break;

		usleep_range(1000, 2000);
	}

	if (val & HDMI_PHY_TX_PHY_LOCK)
		dev_warn(hdmi->dev, "PHY failed to power down\n");
	else
		dev_dbg(hdmi->dev, "PHY powered down in %u iterations\n", i);

	dw_hdmi_phy_gen2_pddq(hdmi, 1);
}