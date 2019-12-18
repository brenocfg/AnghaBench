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
struct phy_device {scalar_t__ interface; scalar_t__ link; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_FIBRE_BIT ; 
 int /*<<< orphan*/  MII_MARVELL_COPPER_PAGE ; 
 int /*<<< orphan*/  MII_MARVELL_FIBER_PAGE ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 scalar_t__ linkmode_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int marvell_read_status_page (struct phy_device*,int /*<<< orphan*/ ) ; 
 int marvell_set_page (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_read_status(struct phy_device *phydev)
{
	int err;

	/* Check the fiber mode first */
	if (linkmode_test_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
			      phydev->supported) &&
	    phydev->interface != PHY_INTERFACE_MODE_SGMII) {
		err = marvell_set_page(phydev, MII_MARVELL_FIBER_PAGE);
		if (err < 0)
			goto error;

		err = marvell_read_status_page(phydev, MII_MARVELL_FIBER_PAGE);
		if (err < 0)
			goto error;

		/* If the fiber link is up, it is the selected and
		 * used link. In this case, we need to stay in the
		 * fiber page. Please to be careful about that, avoid
		 * to restore Copper page in other functions which
		 * could break the behaviour for some fiber phy like
		 * 88E1512.
		 */
		if (phydev->link)
			return 0;

		/* If fiber link is down, check and save copper mode state */
		err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
		if (err < 0)
			goto error;
	}

	return marvell_read_status_page(phydev, MII_MARVELL_COPPER_PAGE);

error:
	marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	return err;
}