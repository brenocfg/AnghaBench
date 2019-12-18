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
 int /*<<< orphan*/  DP83811_DEVADDR ; 
 int /*<<< orphan*/  DP83811_WOL_CLR_INDICATION ; 
 int /*<<< orphan*/  MII_DP83811_WOL_CFG ; 
 int /*<<< orphan*/  genphy_resume (struct phy_device*) ; 
 int /*<<< orphan*/  phy_set_bits_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dp83811_resume(struct phy_device *phydev)
{
	genphy_resume(phydev);

	phy_set_bits_mmd(phydev, DP83811_DEVADDR, MII_DP83811_WOL_CFG,
			 DP83811_WOL_CLR_INDICATION);

	return 0;
}