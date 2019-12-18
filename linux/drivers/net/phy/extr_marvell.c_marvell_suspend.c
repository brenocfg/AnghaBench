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
struct phy_device {int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_FIBRE_BIT ; 
 int /*<<< orphan*/  MII_MARVELL_COPPER_PAGE ; 
 int /*<<< orphan*/  MII_MARVELL_FIBER_PAGE ; 
 int genphy_suspend (struct phy_device*) ; 
 int /*<<< orphan*/  linkmode_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int marvell_set_page (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int marvell_suspend(struct phy_device *phydev)
{
	int err;

	/* Suspend the fiber mode first */
	if (!linkmode_test_bit(ETHTOOL_LINK_MODE_FIBRE_BIT,
			       phydev->supported)) {
		err = marvell_set_page(phydev, MII_MARVELL_FIBER_PAGE);
		if (err < 0)
			goto error;

		/* With the page set, use the generic suspend */
		err = genphy_suspend(phydev);
		if (err < 0)
			goto error;

		/* Then, the copper link */
		err = marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
		if (err < 0)
			goto error;
	}

	/* With the page set, use the generic suspend */
	return genphy_suspend(phydev);

error:
	marvell_set_page(phydev, MII_MARVELL_COPPER_PAGE);
	return err;
}