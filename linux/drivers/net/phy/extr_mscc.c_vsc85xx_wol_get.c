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
typedef  int u16 ;
struct phy_device {int /*<<< orphan*/  lock; } ;
struct ethtool_wolinfo {int wolopts; int* sopass; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_EXTENDED_2 ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_LOWER_PASSWD ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_MAC_CONTROL ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_MID_PASSWD ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_UPPER_PASSWD ; 
 int SECURE_ON_ENABLE ; 
 int WAKE_MAGICSECURE ; 
 int __phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_restore_page (struct phy_device*,int,int) ; 
 int phy_select_page (struct phy_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vsc85xx_wol_get(struct phy_device *phydev,
			    struct ethtool_wolinfo *wol)
{
	int rc;
	u16 reg_val;
	u8  i;
	u16 pwd[3] = {0, 0, 0};
	struct ethtool_wolinfo *wol_conf = wol;

	mutex_lock(&phydev->lock);
	rc = phy_select_page(phydev, MSCC_PHY_PAGE_EXTENDED_2);
	if (rc < 0)
		goto out_unlock;

	reg_val = __phy_read(phydev, MSCC_PHY_WOL_MAC_CONTROL);
	if (reg_val & SECURE_ON_ENABLE)
		wol_conf->wolopts |= WAKE_MAGICSECURE;
	if (wol_conf->wolopts & WAKE_MAGICSECURE) {
		pwd[0] = __phy_read(phydev, MSCC_PHY_WOL_LOWER_PASSWD);
		pwd[1] = __phy_read(phydev, MSCC_PHY_WOL_MID_PASSWD);
		pwd[2] = __phy_read(phydev, MSCC_PHY_WOL_UPPER_PASSWD);
		for (i = 0; i < ARRAY_SIZE(pwd); i++) {
			wol_conf->sopass[5 - i * 2] = pwd[i] & 0x00ff;
			wol_conf->sopass[5 - (i * 2 + 1)] = (pwd[i] & 0xff00)
							    >> 8;
		}
	}

out_unlock:
	phy_restore_page(phydev, rc, rc > 0 ? 0 : rc);
	mutex_unlock(&phydev->lock);
}