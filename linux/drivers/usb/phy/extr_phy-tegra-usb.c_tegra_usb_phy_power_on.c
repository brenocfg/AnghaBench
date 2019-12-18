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
struct tegra_usb_phy {scalar_t__ is_ulpi_phy; } ;

/* Variables and functions */
 int ulpi_phy_power_on (struct tegra_usb_phy*) ; 
 int utmi_phy_power_on (struct tegra_usb_phy*) ; 

__attribute__((used)) static int tegra_usb_phy_power_on(struct tegra_usb_phy *phy)
{
	if (phy->is_ulpi_phy)
		return ulpi_phy_power_on(phy);
	else
		return utmi_phy_power_on(phy);
}