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
struct phy_device {int /*<<< orphan*/  autoneg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int BMCR_ANENABLE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dp83848_config_init(struct phy_device *phydev)
{
	int val;

	/* DP83620 always reports Auto Negotiation Ability on BMSR. Instead,
	 * we check initial value of BMCR Auto negotiation enable bit
	 */
	val = phy_read(phydev, MII_BMCR);
	if (!(val & BMCR_ANENABLE))
		phydev->autoneg = AUTONEG_DISABLE;

	return 0;
}