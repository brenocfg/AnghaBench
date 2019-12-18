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
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_88E1318S_PHY_WOL_CTRL ; 
 int MII_88E1318S_PHY_WOL_CTRL_MAGIC_PACKET_MATCH_ENABLE ; 
 int /*<<< orphan*/  MII_MARVELL_WOL_PAGE ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 int __phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_restore_page (struct phy_device*,int,int) ; 
 int phy_select_page (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void m88e1318_get_wol(struct phy_device *phydev,
			     struct ethtool_wolinfo *wol)
{
	int oldpage, ret = 0;

	wol->supported = WAKE_MAGIC;
	wol->wolopts = 0;

	oldpage = phy_select_page(phydev, MII_MARVELL_WOL_PAGE);
	if (oldpage < 0)
		goto error;

	ret = __phy_read(phydev, MII_88E1318S_PHY_WOL_CTRL);
	if (ret & MII_88E1318S_PHY_WOL_CTRL_MAGIC_PACKET_MATCH_ENABLE)
		wol->wolopts |= WAKE_MAGIC;

error:
	phy_restore_page(phydev, oldpage, ret);
}