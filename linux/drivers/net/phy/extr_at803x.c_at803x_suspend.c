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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT803X_INTR_ENABLE ; 
 int AT803X_INTR_ENABLE_WOL ; 
 int BMCR_ISOLATE ; 
 int BMCR_PDOWN ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  phy_modify (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at803x_suspend(struct phy_device *phydev)
{
	int value;
	int wol_enabled;

	value = phy_read(phydev, AT803X_INTR_ENABLE);
	wol_enabled = value & AT803X_INTR_ENABLE_WOL;

	if (wol_enabled)
		value = BMCR_ISOLATE;
	else
		value = BMCR_PDOWN;

	phy_modify(phydev, MII_BMCR, 0, value);

	return 0;
}