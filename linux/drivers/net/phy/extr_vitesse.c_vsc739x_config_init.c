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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_modify (struct phy_device*,int,int,int) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int,int) ; 
 int /*<<< orphan*/  vsc73xx_config_init (struct phy_device*) ; 

__attribute__((used)) static int vsc739x_config_init(struct phy_device *phydev)
{
	/* This magic sequence appears in the VSC7395 SparX-G5e application
	 * note "VSC7395/VSC7398 PHY Configuration"
	 *
	 * Maybe one day we will get to know what it all means.
	 */
	phy_write(phydev, 0x1f, 0x2a30);
	phy_modify(phydev, 0x08, 0x0200, 0x0200);
	phy_write(phydev, 0x1f, 0x52b5);
	phy_write(phydev, 0x10, 0xb68a);
	phy_modify(phydev, 0x12, 0xff07, 0x0003);
	phy_modify(phydev, 0x11, 0x00ff, 0x00a2);
	phy_write(phydev, 0x10, 0x968a);
	phy_write(phydev, 0x1f, 0x2a30);
	phy_modify(phydev, 0x08, 0x0200, 0x0000);
	phy_write(phydev, 0x1f, 0x0000);

	phy_write(phydev, 0x1f, 0x0000);
	phy_write(phydev, 0x12, 0x0048);
	phy_write(phydev, 0x1f, 0x2a30);
	phy_modify(phydev, 0x16, 0x0fc0, 0x0240);
	phy_modify(phydev, 0x14, 0x6000, 0x4000);
	phy_write(phydev, 0x1f, 0x0001);
	phy_modify(phydev, 0x14, 0xe000, 0x6000);
	phy_write(phydev, 0x1f, 0x0000);

	vsc73xx_config_init(phydev);

	return 0;
}