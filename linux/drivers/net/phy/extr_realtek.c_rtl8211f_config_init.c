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
struct phy_device {int interface; } ;

/* Variables and functions */
#define  PHY_INTERFACE_MODE_RGMII 131 
#define  PHY_INTERFACE_MODE_RGMII_ID 130 
#define  PHY_INTERFACE_MODE_RGMII_RXID 129 
#define  PHY_INTERFACE_MODE_RGMII_TXID 128 
 int /*<<< orphan*/  RTL8211F_TX_DELAY ; 
 int phy_modify_paged (struct phy_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8211f_config_init(struct phy_device *phydev)
{
	u16 val;

	/* enable TX-delay for rgmii-{id,txid}, and disable it for rgmii and
	 * rgmii-rxid. The RX-delay can be enabled by the external RXDLY pin.
	 */
	switch (phydev->interface) {
	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_RXID:
		val = 0;
		break;
	case PHY_INTERFACE_MODE_RGMII_ID:
	case PHY_INTERFACE_MODE_RGMII_TXID:
		val = RTL8211F_TX_DELAY;
		break;
	default: /* the rest of the modes imply leaving delay as is. */
		return 0;
	}

	return phy_modify_paged(phydev, 0xd08, 0x11, RTL8211F_TX_DELAY, val);
}