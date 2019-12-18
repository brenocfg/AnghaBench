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
struct mvebu_a3700_comphy_lane {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPHY_SIP_POWER_OFF ; 
 int mvebu_a3700_comphy_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mvebu_a3700_comphy_lane* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int mvebu_a3700_comphy_power_off(struct phy *phy)
{
	struct mvebu_a3700_comphy_lane *lane = phy_get_drvdata(phy);

	return mvebu_a3700_comphy_smc(COMPHY_SIP_POWER_OFF, lane->id, 0);
}