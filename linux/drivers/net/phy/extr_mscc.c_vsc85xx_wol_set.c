#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u16 ;
struct phy_device {int /*<<< orphan*/  lock; TYPE_1__* attached_dev; } ;
struct ethtool_wolinfo {int wolopts; int* sopass; } ;
struct TYPE_2__ {size_t* dev_addr; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  MII_VSC85XX_INT_MASK ; 
 int MII_VSC85XX_INT_MASK_WOL ; 
 int /*<<< orphan*/  MII_VSC85XX_INT_STATUS ; 
 int /*<<< orphan*/  MSCC_PHY_PAGE_EXTENDED_2 ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_LOWER_MAC_ADDR ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_LOWER_PASSWD ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_MAC_CONTROL ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_MID_MAC_ADDR ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_MID_PASSWD ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_UPPER_MAC_ADDR ; 
 int /*<<< orphan*/  MSCC_PHY_WOL_UPPER_PASSWD ; 
 int SECURE_ON_ENABLE ; 
 int WAKE_MAGIC ; 
 int WAKE_MAGICSECURE ; 
 int __phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_restore_page (struct phy_device*,int,int) ; 
 int phy_select_page (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vsc85xx_wol_set(struct phy_device *phydev,
			   struct ethtool_wolinfo *wol)
{
	int rc;
	u16 reg_val;
	u8  i;
	u16 pwd[3] = {0, 0, 0};
	struct ethtool_wolinfo *wol_conf = wol;
	u8 *mac_addr = phydev->attached_dev->dev_addr;

	mutex_lock(&phydev->lock);
	rc = phy_select_page(phydev, MSCC_PHY_PAGE_EXTENDED_2);
	if (rc < 0) {
		rc = phy_restore_page(phydev, rc, rc);
		goto out_unlock;
	}

	if (wol->wolopts & WAKE_MAGIC) {
		/* Store the device address for the magic packet */
		for (i = 0; i < ARRAY_SIZE(pwd); i++)
			pwd[i] = mac_addr[5 - (i * 2 + 1)] << 8 |
				 mac_addr[5 - i * 2];
		__phy_write(phydev, MSCC_PHY_WOL_LOWER_MAC_ADDR, pwd[0]);
		__phy_write(phydev, MSCC_PHY_WOL_MID_MAC_ADDR, pwd[1]);
		__phy_write(phydev, MSCC_PHY_WOL_UPPER_MAC_ADDR, pwd[2]);
	} else {
		__phy_write(phydev, MSCC_PHY_WOL_LOWER_MAC_ADDR, 0);
		__phy_write(phydev, MSCC_PHY_WOL_MID_MAC_ADDR, 0);
		__phy_write(phydev, MSCC_PHY_WOL_UPPER_MAC_ADDR, 0);
	}

	if (wol_conf->wolopts & WAKE_MAGICSECURE) {
		for (i = 0; i < ARRAY_SIZE(pwd); i++)
			pwd[i] = wol_conf->sopass[5 - (i * 2 + 1)] << 8 |
				 wol_conf->sopass[5 - i * 2];
		__phy_write(phydev, MSCC_PHY_WOL_LOWER_PASSWD, pwd[0]);
		__phy_write(phydev, MSCC_PHY_WOL_MID_PASSWD, pwd[1]);
		__phy_write(phydev, MSCC_PHY_WOL_UPPER_PASSWD, pwd[2]);
	} else {
		__phy_write(phydev, MSCC_PHY_WOL_LOWER_PASSWD, 0);
		__phy_write(phydev, MSCC_PHY_WOL_MID_PASSWD, 0);
		__phy_write(phydev, MSCC_PHY_WOL_UPPER_PASSWD, 0);
	}

	reg_val = __phy_read(phydev, MSCC_PHY_WOL_MAC_CONTROL);
	if (wol_conf->wolopts & WAKE_MAGICSECURE)
		reg_val |= SECURE_ON_ENABLE;
	else
		reg_val &= ~SECURE_ON_ENABLE;
	__phy_write(phydev, MSCC_PHY_WOL_MAC_CONTROL, reg_val);

	rc = phy_restore_page(phydev, rc, rc > 0 ? 0 : rc);
	if (rc < 0)
		goto out_unlock;

	if (wol->wolopts & WAKE_MAGIC) {
		/* Enable the WOL interrupt */
		reg_val = phy_read(phydev, MII_VSC85XX_INT_MASK);
		reg_val |= MII_VSC85XX_INT_MASK_WOL;
		rc = phy_write(phydev, MII_VSC85XX_INT_MASK, reg_val);
		if (rc)
			goto out_unlock;
	} else {
		/* Disable the WOL interrupt */
		reg_val = phy_read(phydev, MII_VSC85XX_INT_MASK);
		reg_val &= (~MII_VSC85XX_INT_MASK_WOL);
		rc = phy_write(phydev, MII_VSC85XX_INT_MASK, reg_val);
		if (rc)
			goto out_unlock;
	}
	/* Clear WOL iterrupt status */
	reg_val = phy_read(phydev, MII_VSC85XX_INT_STATUS);

out_unlock:
	mutex_unlock(&phydev->lock);

	return rc;
}