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
 int /*<<< orphan*/  DP83822_DEVADDR ; 
 int DP83822_WOL_EN ; 
 int /*<<< orphan*/  MII_DP83822_WOL_CFG ; 
 int /*<<< orphan*/  genphy_suspend (struct phy_device*) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dp83822_suspend(struct phy_device *phydev)
{
	int value;

	value = phy_read_mmd(phydev, DP83822_DEVADDR, MII_DP83822_WOL_CFG);

	if (!(value & DP83822_WOL_EN))
		genphy_suspend(phydev);

	return 0;
}