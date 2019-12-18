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
 int /*<<< orphan*/  MII_MARVELL_PHY_PAGE ; 
 int __phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int marvell_write_page(struct phy_device *phydev, int page)
{
	return __phy_write(phydev, MII_MARVELL_PHY_PAGE, page);
}