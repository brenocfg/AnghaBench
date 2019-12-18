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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int __phy_read_mmd (struct phy_device*,int,int /*<<< orphan*/ ) ; 
 int __phy_write_mmd (struct phy_device*,int,int /*<<< orphan*/ ,int) ; 

int __phy_modify_mmd_changed(struct phy_device *phydev, int devad, u32 regnum,
			     u16 mask, u16 set)
{
	int new, ret;

	ret = __phy_read_mmd(phydev, devad, regnum);
	if (ret < 0)
		return ret;

	new = (ret & ~mask) | set;
	if (new == ret)
		return 0;

	ret = __phy_write_mmd(phydev, devad, regnum, new);

	return ret < 0 ? ret : 1;
}