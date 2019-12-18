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
 int /*<<< orphan*/  LAN88XX_EXT_PAGE_ACCESS_TR ; 
 int /*<<< orphan*/  LAN88XX_EXT_PAGE_TR_CR ; 
 int /*<<< orphan*/  LAN88XX_EXT_PAGE_TR_HIGH_DATA ; 
 int /*<<< orphan*/  LAN88XX_EXT_PAGE_TR_LOW_DATA ; 
 int __phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int __phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lan88xx_write_page (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_restore_page (struct phy_device*,int,int) ; 
 int phy_save_page (struct phy_device*) ; 
 int /*<<< orphan*/  phydev_warn (struct phy_device*,char*,...) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lan88xx_TR_reg_set(struct phy_device *phydev, u16 regaddr,
			      u32 data)
{
	int val, save_page, ret = 0;
	u16 buf;

	/* Save current page */
	save_page = phy_save_page(phydev);
	if (save_page < 0) {
		phydev_warn(phydev, "Failed to get current page\n");
		goto err;
	}

	/* Switch to TR page */
	lan88xx_write_page(phydev, LAN88XX_EXT_PAGE_ACCESS_TR);

	ret = __phy_write(phydev, LAN88XX_EXT_PAGE_TR_LOW_DATA,
			  (data & 0xFFFF));
	if (ret < 0) {
		phydev_warn(phydev, "Failed to write TR low data\n");
		goto err;
	}

	ret = __phy_write(phydev, LAN88XX_EXT_PAGE_TR_HIGH_DATA,
			  (data & 0x00FF0000) >> 16);
	if (ret < 0) {
		phydev_warn(phydev, "Failed to write TR high data\n");
		goto err;
	}

	/* Config control bits [15:13] of register */
	buf = (regaddr & ~(0x3 << 13));/* Clr [14:13] to write data in reg */
	buf |= 0x8000; /* Set [15] to Packet transmit */

	ret = __phy_write(phydev, LAN88XX_EXT_PAGE_TR_CR, buf);
	if (ret < 0) {
		phydev_warn(phydev, "Failed to write data in reg\n");
		goto err;
	}

	usleep_range(1000, 2000);/* Wait for Data to be written */
	val = __phy_read(phydev, LAN88XX_EXT_PAGE_TR_CR);
	if (!(val & 0x8000))
		phydev_warn(phydev, "TR Register[0x%X] configuration failed\n",
			    regaddr);
err:
	return phy_restore_page(phydev, save_page, ret);
}