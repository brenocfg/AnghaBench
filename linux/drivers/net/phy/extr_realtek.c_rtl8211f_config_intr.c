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
struct phy_device {scalar_t__ interrupts; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 scalar_t__ RTL8211F_INER_LINK_STATUS ; 
 int /*<<< orphan*/  RTL821x_INER ; 
 int phy_write_paged (struct phy_device*,int,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rtl8211f_config_intr(struct phy_device *phydev)
{
	u16 val;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED)
		val = RTL8211F_INER_LINK_STATUS;
	else
		val = 0;

	return phy_write_paged(phydev, 0xa42, RTL821x_INER, val);
}