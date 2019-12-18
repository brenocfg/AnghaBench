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
struct phy {int dummy; } ;
struct mvebu_a3700_comphy_lane {int mode; int submode; int /*<<< orphan*/  dev; int /*<<< orphan*/  port; int /*<<< orphan*/  id; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int PHY_INTERFACE_MODE_1000BASEX ; 
 int PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mvebu_a3700_comphy_get_fw_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct mvebu_a3700_comphy_lane* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int mvebu_a3700_comphy_set_mode(struct phy *phy, enum phy_mode mode,
				       int submode)
{
	struct mvebu_a3700_comphy_lane *lane = phy_get_drvdata(phy);
	int fw_mode;

	if (submode == PHY_INTERFACE_MODE_1000BASEX)
		submode = PHY_INTERFACE_MODE_SGMII;

	fw_mode = mvebu_a3700_comphy_get_fw_mode(lane->id, lane->port, mode,
						 submode);
	if (fw_mode < 0) {
		dev_err(lane->dev, "invalid COMPHY mode\n");
		return fw_mode;
	}

	/* Just remember the mode, ->power_on() will do the real setup */
	lane->mode = mode;
	lane->submode = submode;

	return 0;
}