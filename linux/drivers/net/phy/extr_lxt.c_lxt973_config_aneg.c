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
struct phy_device {scalar_t__ priv; } ;

/* Variables and functions */
 int genphy_config_aneg (struct phy_device*) ; 

__attribute__((used)) static int lxt973_config_aneg(struct phy_device *phydev)
{
	/* Do nothing if port is in fiber mode. */
	return phydev->priv ? 0 : genphy_config_aneg(phydev);
}