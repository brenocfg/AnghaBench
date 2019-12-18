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
typedef  int u16 ;
struct phy_device {int interface; } ;

/* Variables and functions */
#define  PHY_INTERFACE_MODE_RGMII 131 
#define  PHY_INTERFACE_MODE_RGMII_ID 130 
#define  PHY_INTERFACE_MODE_RGMII_RXID 129 
#define  PHY_INTERFACE_MODE_RGMII_TXID 128 
 int RTL8211E_RX_DELAY ; 
 int RTL8211E_TX_DELAY ; 
 int /*<<< orphan*/  RTL821x_EXT_PAGE_SELECT ; 
 int __phy_modify (struct phy_device*,int,int,int) ; 
 int __phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int phy_restore_page (struct phy_device*,int,int) ; 
 int phy_select_page (struct phy_device*,int) ; 

__attribute__((used)) static int rtl8211e_config_init(struct phy_device *phydev)
{
	int ret = 0, oldpage;
	u16 val;

	/* enable TX/RX delay for rgmii-* modes, and disable them for rgmii. */
	switch (phydev->interface) {
	case PHY_INTERFACE_MODE_RGMII:
		val = 0;
		break;
	case PHY_INTERFACE_MODE_RGMII_ID:
		val = RTL8211E_TX_DELAY | RTL8211E_RX_DELAY;
		break;
	case PHY_INTERFACE_MODE_RGMII_RXID:
		val = RTL8211E_RX_DELAY;
		break;
	case PHY_INTERFACE_MODE_RGMII_TXID:
		val = RTL8211E_TX_DELAY;
		break;
	default: /* the rest of the modes imply leaving delays as is. */
		return 0;
	}

	/* According to a sample driver there is a 0x1c config register on the
	 * 0xa4 extension page (0x7) layout. It can be used to disable/enable
	 * the RX/TX delays otherwise controlled by RXDLY/TXDLY pins. It can
	 * also be used to customize the whole configuration register:
	 * 8:6 = PHY Address, 5:4 = Auto-Negotiation, 3 = Interface Mode Select,
	 * 2 = RX Delay, 1 = TX Delay, 0 = SELRGV (see original PHY datasheet
	 * for details).
	 */
	oldpage = phy_select_page(phydev, 0x7);
	if (oldpage < 0)
		goto err_restore_page;

	ret = __phy_write(phydev, RTL821x_EXT_PAGE_SELECT, 0xa4);
	if (ret)
		goto err_restore_page;

	ret = __phy_modify(phydev, 0x1c, RTL8211E_TX_DELAY | RTL8211E_RX_DELAY,
			   val);

err_restore_page:
	return phy_restore_page(phydev, oldpage, ret);
}