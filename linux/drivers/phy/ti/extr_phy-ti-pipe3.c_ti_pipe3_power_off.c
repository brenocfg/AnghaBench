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
struct ti_pipe3 {int /*<<< orphan*/  power_reg; int /*<<< orphan*/  phy_power_syscon; int /*<<< orphan*/  control_dev; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE3_PHY_PWRCTL_CLK_CMD_MASK ; 
 int /*<<< orphan*/  omap_control_phy_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ti_pipe3* phy_get_drvdata (struct phy*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_pipe3_power_off(struct phy *x)
{
	int ret;
	struct ti_pipe3 *phy = phy_get_drvdata(x);

	if (!phy->phy_power_syscon) {
		omap_control_phy_power(phy->control_dev, 0);
		return 0;
	}

	ret = regmap_update_bits(phy->phy_power_syscon, phy->power_reg,
				 PIPE3_PHY_PWRCTL_CLK_CMD_MASK, 0);
	return ret;
}