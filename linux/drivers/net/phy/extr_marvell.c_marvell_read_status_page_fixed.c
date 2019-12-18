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
struct phy_device {int /*<<< orphan*/  lp_advertising; scalar_t__ asym_pause; scalar_t__ pause; int /*<<< orphan*/  speed; int /*<<< orphan*/  duplex; } ;

/* Variables and functions */
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int BMCR_SPEED1000 ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  linkmode_zero (int /*<<< orphan*/ ) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_read_status_page_fixed(struct phy_device *phydev)
{
	int bmcr = phy_read(phydev, MII_BMCR);

	if (bmcr < 0)
		return bmcr;

	if (bmcr & BMCR_FULLDPLX)
		phydev->duplex = DUPLEX_FULL;
	else
		phydev->duplex = DUPLEX_HALF;

	if (bmcr & BMCR_SPEED1000)
		phydev->speed = SPEED_1000;
	else if (bmcr & BMCR_SPEED100)
		phydev->speed = SPEED_100;
	else
		phydev->speed = SPEED_10;

	phydev->pause = 0;
	phydev->asym_pause = 0;
	linkmode_zero(phydev->lp_advertising);

	return 0;
}