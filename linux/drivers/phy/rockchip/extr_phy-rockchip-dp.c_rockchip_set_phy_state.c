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
struct rockchip_dp_phy {int /*<<< orphan*/  grf; int /*<<< orphan*/  phy_24m; int /*<<< orphan*/  dev; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int GRF_EDP_PHY_SIDDQ_HIWORD_MASK ; 
 int GRF_EDP_PHY_SIDDQ_OFF ; 
 int GRF_EDP_PHY_SIDDQ_ON ; 
 int /*<<< orphan*/  GRF_SOC_CON12 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct rockchip_dp_phy* phy_get_drvdata (struct phy*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rockchip_set_phy_state(struct phy *phy, bool enable)
{
	struct rockchip_dp_phy *dp = phy_get_drvdata(phy);
	int ret;

	if (enable) {
		ret = regmap_write(dp->grf, GRF_SOC_CON12,
				   GRF_EDP_PHY_SIDDQ_HIWORD_MASK |
				   GRF_EDP_PHY_SIDDQ_ON);
		if (ret < 0) {
			dev_err(dp->dev, "Can't enable PHY power %d\n", ret);
			return ret;
		}

		ret = clk_prepare_enable(dp->phy_24m);
	} else {
		clk_disable_unprepare(dp->phy_24m);

		ret = regmap_write(dp->grf, GRF_SOC_CON12,
				   GRF_EDP_PHY_SIDDQ_HIWORD_MASK |
				   GRF_EDP_PHY_SIDDQ_OFF);
	}

	return ret;
}