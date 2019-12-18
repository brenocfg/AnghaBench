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
struct phy_device {scalar_t__ interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_TX_VEND_INT_MASK2 ; 
 int MDIO_AN_TX_VEND_INT_MASK2_LINK ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_VEND1 ; 
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 int /*<<< orphan*/  VEND1_GLOBAL_INT_STD_MASK ; 
 int VEND1_GLOBAL_INT_STD_MASK_ALL ; 
 int /*<<< orphan*/  VEND1_GLOBAL_INT_VEND_MASK ; 
 int VEND1_GLOBAL_INT_VEND_MASK_AN ; 
 int VEND1_GLOBAL_INT_VEND_MASK_GLOBAL3 ; 
 int phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aqr_config_intr(struct phy_device *phydev)
{
	bool en = phydev->interrupts == PHY_INTERRUPT_ENABLED;
	int err;

	err = phy_write_mmd(phydev, MDIO_MMD_AN, MDIO_AN_TX_VEND_INT_MASK2,
			    en ? MDIO_AN_TX_VEND_INT_MASK2_LINK : 0);
	if (err < 0)
		return err;

	err = phy_write_mmd(phydev, MDIO_MMD_VEND1, VEND1_GLOBAL_INT_STD_MASK,
			    en ? VEND1_GLOBAL_INT_STD_MASK_ALL : 0);
	if (err < 0)
		return err;

	return phy_write_mmd(phydev, MDIO_MMD_VEND1, VEND1_GLOBAL_INT_VEND_MASK,
			     en ? VEND1_GLOBAL_INT_VEND_MASK_GLOBAL3 |
			     VEND1_GLOBAL_INT_VEND_MASK_AN : 0);
}