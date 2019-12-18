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
 int DP83822_WOL_MAGIC_EN ; 
 int DP83822_WOL_SECURE_ON ; 
 int /*<<< orphan*/  MII_DP83822_WOL_CFG ; 
 int phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dp83822_config_init(struct phy_device *phydev)
{
	int value;

	value = DP83822_WOL_MAGIC_EN | DP83822_WOL_SECURE_ON | DP83822_WOL_EN;

	return phy_write_mmd(phydev, DP83822_DEVADDR, MII_DP83822_WOL_CFG,
	      value);
}