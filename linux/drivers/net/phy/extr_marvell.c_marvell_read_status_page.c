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
struct phy_device {scalar_t__ autoneg; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int MII_MARVELL_FIBER_PAGE ; 
 int marvell_read_status_page_an (struct phy_device*,int) ; 
 int marvell_read_status_page_fixed (struct phy_device*) ; 
 int marvell_update_link (struct phy_device*,int) ; 

__attribute__((used)) static int marvell_read_status_page(struct phy_device *phydev, int page)
{
	int fiber;
	int err;

	/* Detect and update the link, but return if there
	 * was an error
	 */
	if (page == MII_MARVELL_FIBER_PAGE)
		fiber = 1;
	else
		fiber = 0;

	err = marvell_update_link(phydev, fiber);
	if (err)
		return err;

	if (phydev->autoneg == AUTONEG_ENABLE)
		err = marvell_read_status_page_an(phydev, fiber);
	else
		err = marvell_read_status_page_fixed(phydev);

	return err;
}