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
struct ksz_device {int phy_port_cnt; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_INTERFACE_MODE_GMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_MII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_NA ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_ID ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_RXID ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_TXID ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RMII ; 
 int PORT_RGMII_ID_EG_ENABLE ; 
 int PORT_RGMII_ID_IG_ENABLE ; 
 int /*<<< orphan*/  REG_PORT_XMII_CTRL_1 ; 
 int ksz9477_get_gbit (struct ksz_device*,int) ; 
 int ksz9477_get_xmii (struct ksz_device*,int) ; 
 int /*<<< orphan*/  ksz_pread8 (struct ksz_device*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static phy_interface_t ksz9477_get_interface(struct ksz_device *dev, int port)
{
	phy_interface_t interface;
	bool gbit;
	int mode;
	u8 data8;

	if (port < dev->phy_port_cnt)
		return PHY_INTERFACE_MODE_NA;
	ksz_pread8(dev, port, REG_PORT_XMII_CTRL_1, &data8);
	gbit = ksz9477_get_gbit(dev, data8);
	mode = ksz9477_get_xmii(dev, data8);
	switch (mode) {
	case 2:
		interface = PHY_INTERFACE_MODE_GMII;
		if (gbit)
			break;
		/* fall through */
	case 0:
		interface = PHY_INTERFACE_MODE_MII;
		break;
	case 1:
		interface = PHY_INTERFACE_MODE_RMII;
		break;
	default:
		interface = PHY_INTERFACE_MODE_RGMII;
		if (data8 & PORT_RGMII_ID_EG_ENABLE)
			interface = PHY_INTERFACE_MODE_RGMII_TXID;
		if (data8 & PORT_RGMII_ID_IG_ENABLE) {
			interface = PHY_INTERFACE_MODE_RGMII_RXID;
			if (data8 & PORT_RGMII_ID_EG_ENABLE)
				interface = PHY_INTERFACE_MODE_RGMII_ID;
		}
		break;
	}
	return interface;
}