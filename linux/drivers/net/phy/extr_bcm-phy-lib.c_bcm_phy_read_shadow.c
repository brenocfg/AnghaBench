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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_BCM54XX_SHD ; 
 int MII_BCM54XX_SHD_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MII_BCM54XX_SHD_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bcm_phy_read_shadow(struct phy_device *phydev, u16 shadow)
{
	phy_write(phydev, MII_BCM54XX_SHD, MII_BCM54XX_SHD_VAL(shadow));
	return MII_BCM54XX_SHD_DATA(phy_read(phydev, MII_BCM54XX_SHD));
}