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
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHY_HT_RF_CTL_CMD ; 
 int /*<<< orphan*/  B43_PHY_HT_RF_CTL_CMD_CHIP0_PU ; 
 int /*<<< orphan*/  B43_PHY_HT_RF_CTL_CMD_FORCE ; 
 int /*<<< orphan*/  b43_phy_mask (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void b43_radio_2059_init_pre(struct b43_wldev *dev)
{
	b43_phy_mask(dev, B43_PHY_HT_RF_CTL_CMD, ~B43_PHY_HT_RF_CTL_CMD_CHIP0_PU);
	b43_phy_set(dev, B43_PHY_HT_RF_CTL_CMD, B43_PHY_HT_RF_CTL_CMD_FORCE);
	b43_phy_mask(dev, B43_PHY_HT_RF_CTL_CMD, ~B43_PHY_HT_RF_CTL_CMD_FORCE);
	b43_phy_set(dev, B43_PHY_HT_RF_CTL_CMD, B43_PHY_HT_RF_CTL_CMD_CHIP0_PU);
}