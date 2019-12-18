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
typedef  scalar_t__ u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ MDIO_AN_EEE_ADV2 ; 
 int MDIO_MMD_AN ; 
 int __phy_write (struct phy_device*,int,scalar_t__) ; 
 int /*<<< orphan*/  rtl821x_write_page (struct phy_device*,int) ; 
 int rtlgen_write_mmd (struct phy_device*,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int rtl8125_write_mmd(struct phy_device *phydev, int devnum, u16 regnum,
			     u16 val)
{
	int ret = rtlgen_write_mmd(phydev, devnum, regnum, val);

	if (ret != -EOPNOTSUPP)
		return ret;

	if (devnum == MDIO_MMD_AN && regnum == MDIO_AN_EEE_ADV2) {
		rtl821x_write_page(phydev, 0xa6d);
		ret = __phy_write(phydev, 0x12, val);
		rtl821x_write_page(phydev, 0);
	}

	return ret;
}