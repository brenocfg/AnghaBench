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
struct phy {int dummy; } ;
struct exynos_dp_video_phy {TYPE_1__* drvdata; int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy_ctrl_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS4_PHY_ENABLE ; 
 struct exynos_dp_video_phy* phy_get_drvdata (struct phy*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_dp_video_phy_power_on(struct phy *phy)
{
	struct exynos_dp_video_phy *state = phy_get_drvdata(phy);

	/* Disable power isolation on DP-PHY */
	return regmap_update_bits(state->regs, state->drvdata->phy_ctrl_offset,
				  EXYNOS4_PHY_ENABLE, EXYNOS4_PHY_ENABLE);
}