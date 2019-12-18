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
 int /*<<< orphan*/  MII_BMCR ; 
 int genphy_soft_reset (struct phy_device*) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asix_soft_reset(struct phy_device *phydev)
{
	int ret;

	/* Asix PHY won't reset unless reset bit toggles */
	ret = phy_write(phydev, MII_BMCR, 0);
	if (ret < 0)
		return ret;

	return genphy_soft_reset(phydev);
}