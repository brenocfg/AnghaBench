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
struct phy_device {int mdix_ctrl; } ;

/* Variables and functions */
#define  ETH_TP_MDI 130 
#define  ETH_TP_MDI_AUTO 129 
#define  ETH_TP_MDI_X 128 
 int /*<<< orphan*/  LAN88XX_EXT_MODE_CTRL ; 
 int LAN88XX_EXT_MODE_CTRL_AUTO_MDIX_ ; 
 int LAN88XX_EXT_MODE_CTRL_MDIX_MASK_ ; 
 int LAN88XX_EXT_MODE_CTRL_MDI_ ; 
 int LAN88XX_EXT_MODE_CTRL_MDI_X_ ; 
 int /*<<< orphan*/  LAN88XX_EXT_PAGE_ACCESS ; 
 int LAN88XX_EXT_PAGE_SPACE_0 ; 
 int LAN88XX_EXT_PAGE_SPACE_1 ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lan88xx_set_mdix(struct phy_device *phydev)
{
	int buf;
	int val;

	switch (phydev->mdix_ctrl) {
	case ETH_TP_MDI:
		val = LAN88XX_EXT_MODE_CTRL_MDI_;
		break;
	case ETH_TP_MDI_X:
		val = LAN88XX_EXT_MODE_CTRL_MDI_X_;
		break;
	case ETH_TP_MDI_AUTO:
		val = LAN88XX_EXT_MODE_CTRL_AUTO_MDIX_;
		break;
	default:
		return;
	}

	phy_write(phydev, LAN88XX_EXT_PAGE_ACCESS, LAN88XX_EXT_PAGE_SPACE_1);
	buf = phy_read(phydev, LAN88XX_EXT_MODE_CTRL);
	buf &= ~LAN88XX_EXT_MODE_CTRL_MDIX_MASK_;
	buf |= val;
	phy_write(phydev, LAN88XX_EXT_MODE_CTRL, buf);
	phy_write(phydev, LAN88XX_EXT_PAGE_ACCESS, LAN88XX_EXT_PAGE_SPACE_0);
}