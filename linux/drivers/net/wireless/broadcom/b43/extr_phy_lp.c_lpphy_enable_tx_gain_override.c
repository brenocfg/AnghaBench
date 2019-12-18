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
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_LPPHY_AFE_CTL_OVR ; 
 int /*<<< orphan*/  B43_LPPHY_RF_OVERRIDE_2 ; 
 int /*<<< orphan*/  b43_phy_set (struct b43_wldev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpphy_enable_tx_gain_override(struct b43_wldev *dev)
{
	if (dev->phy.rev < 2)
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x100);
	else {
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x80);
		b43_phy_set(dev, B43_LPPHY_RF_OVERRIDE_2, 0x4000);
	}
	b43_phy_set(dev, B43_LPPHY_AFE_CTL_OVR, 0x40);
}