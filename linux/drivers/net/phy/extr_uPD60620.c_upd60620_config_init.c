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
struct TYPE_2__ {int addr; } ;
struct phy_device {TYPE_1__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_SPM ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int upd60620_config_init(struct phy_device *phydev)
{
	/* Enable support for passive HUBs (could be a strap option) */
	/* PHYMODE: All speeds, HD in parallel detect */
	return phy_write(phydev, PHY_SPM, 0x0180 | phydev->mdio.addr);
}