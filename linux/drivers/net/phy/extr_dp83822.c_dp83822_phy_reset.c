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
 int /*<<< orphan*/  DP83822_HW_RESET ; 
 int /*<<< orphan*/  MII_DP83822_RESET_CTRL ; 
 int /*<<< orphan*/  dp83822_config_init (struct phy_device*) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dp83822_phy_reset(struct phy_device *phydev)
{
	int err;

	err = phy_write(phydev, MII_DP83822_RESET_CTRL, DP83822_HW_RESET);
	if (err < 0)
		return err;

	dp83822_config_init(phydev);

	return 0;
}