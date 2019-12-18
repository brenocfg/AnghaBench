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
typedef  scalar_t__ u8 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DOWNSHIFT_DEV_DISABLE ; 
 int E2BIG ; 
 int /*<<< orphan*/  FIELD_FIT (int,scalar_t__) ; 
 int FIELD_PREP (int,scalar_t__) ; 
 int /*<<< orphan*/  MDIO_AN_VEND_PROV ; 
 int MDIO_AN_VEND_PROV_DOWNSHIFT_EN ; 
 int MDIO_AN_VEND_PROV_DOWNSHIFT_MASK ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int phy_modify_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int aqr107_set_downshift(struct phy_device *phydev, u8 cnt)
{
	int val = 0;

	if (!FIELD_FIT(MDIO_AN_VEND_PROV_DOWNSHIFT_MASK, cnt))
		return -E2BIG;

	if (cnt != DOWNSHIFT_DEV_DISABLE) {
		val = MDIO_AN_VEND_PROV_DOWNSHIFT_EN;
		val |= FIELD_PREP(MDIO_AN_VEND_PROV_DOWNSHIFT_MASK, cnt);
	}

	return phy_modify_mmd(phydev, MDIO_MMD_AN, MDIO_AN_VEND_PROV,
			      MDIO_AN_VEND_PROV_DOWNSHIFT_EN |
			      MDIO_AN_VEND_PROV_DOWNSHIFT_MASK, val);
}