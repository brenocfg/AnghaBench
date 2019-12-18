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
 int /*<<< orphan*/  BMCR_LOOPBACK ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int phy_modify (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int genphy_loopback(struct phy_device *phydev, bool enable)
{
	return phy_modify(phydev, MII_BMCR, BMCR_LOOPBACK,
			  enable ? BMCR_LOOPBACK : 0);
}