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
typedef  int u32 ;
typedef  int u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int KSZPHY_EXTREG_WRITE ; 
 int /*<<< orphan*/  MII_KSZPHY_EXTREG ; 
 int /*<<< orphan*/  MII_KSZPHY_EXTREG_WRITE ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kszphy_extended_write(struct phy_device *phydev,
				u32 regnum, u16 val)
{
	phy_write(phydev, MII_KSZPHY_EXTREG, KSZPHY_EXTREG_WRITE | regnum);
	return phy_write(phydev, MII_KSZPHY_EXTREG_WRITE, val);
}