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
typedef  int u8 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int DOWNSHIFT_DEV_DISABLE ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MDIO_AN_VEND_PROV ; 
 int /*<<< orphan*/  MDIO_AN_VEND_PROV_DOWNSHIFT_EN ; 
 int /*<<< orphan*/  MDIO_AN_VEND_PROV_DOWNSHIFT_MASK ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aqr107_get_downshift(struct phy_device *phydev, u8 *data)
{
	int val, cnt, enable;

	val = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_AN_VEND_PROV);
	if (val < 0)
		return val;

	enable = FIELD_GET(MDIO_AN_VEND_PROV_DOWNSHIFT_EN, val);
	cnt = FIELD_GET(MDIO_AN_VEND_PROV_DOWNSHIFT_MASK, val);

	*data = enable && cnt ? cnt : DOWNSHIFT_DEV_DISABLE;

	return 0;
}