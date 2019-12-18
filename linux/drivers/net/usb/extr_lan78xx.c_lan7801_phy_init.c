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
struct phy_device {int is_internal; int /*<<< orphan*/  drv; } ;
struct lan78xx_net {int /*<<< orphan*/  net; void* interface; int /*<<< orphan*/  mdiobus; } ;
struct fixed_phy_status {int link; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  HW_CFG ; 
 int HW_CFG_CLK125_EN_ ; 
 int HW_CFG_REFCLK25_EN_ ; 
 scalar_t__ IS_ERR (struct phy_device*) ; 
 int /*<<< orphan*/  MAC_RGMII_ID ; 
 int MAC_RGMII_ID_TXC_DELAY_EN_ ; 
 void* PHY_INTERFACE_MODE_RGMII ; 
 int /*<<< orphan*/  PHY_KSZ9031RNX ; 
 int /*<<< orphan*/  PHY_LAN8835 ; 
 int /*<<< orphan*/  PHY_POLL ; 
 int /*<<< orphan*/  RGMII_TX_BYP_DLL ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 struct phy_device* fixed_phy_register (int /*<<< orphan*/ ,struct fixed_phy_status*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz9031rnx_fixup ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lan8835_fixup ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 struct phy_device* phy_find_first (int /*<<< orphan*/ ) ; 
 int phy_register_fixup_for_uid (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct phy_device *lan7801_phy_init(struct lan78xx_net *dev)
{
	u32 buf;
	int ret;
	struct fixed_phy_status fphy_status = {
		.link = 1,
		.speed = SPEED_1000,
		.duplex = DUPLEX_FULL,
	};
	struct phy_device *phydev;

	phydev = phy_find_first(dev->mdiobus);
	if (!phydev) {
		netdev_dbg(dev->net, "PHY Not Found!! Registering Fixed PHY\n");
		phydev = fixed_phy_register(PHY_POLL, &fphy_status, NULL);
		if (IS_ERR(phydev)) {
			netdev_err(dev->net, "No PHY/fixed_PHY found\n");
			return NULL;
		}
		netdev_dbg(dev->net, "Registered FIXED PHY\n");
		dev->interface = PHY_INTERFACE_MODE_RGMII;
		ret = lan78xx_write_reg(dev, MAC_RGMII_ID,
					MAC_RGMII_ID_TXC_DELAY_EN_);
		ret = lan78xx_write_reg(dev, RGMII_TX_BYP_DLL, 0x3D00);
		ret = lan78xx_read_reg(dev, HW_CFG, &buf);
		buf |= HW_CFG_CLK125_EN_;
		buf |= HW_CFG_REFCLK25_EN_;
		ret = lan78xx_write_reg(dev, HW_CFG, buf);
	} else {
		if (!phydev->drv) {
			netdev_err(dev->net, "no PHY driver found\n");
			return NULL;
		}
		dev->interface = PHY_INTERFACE_MODE_RGMII;
		/* external PHY fixup for KSZ9031RNX */
		ret = phy_register_fixup_for_uid(PHY_KSZ9031RNX, 0xfffffff0,
						 ksz9031rnx_fixup);
		if (ret < 0) {
			netdev_err(dev->net, "Failed to register fixup for PHY_KSZ9031RNX\n");
			return NULL;
		}
		/* external PHY fixup for LAN8835 */
		ret = phy_register_fixup_for_uid(PHY_LAN8835, 0xfffffff0,
						 lan8835_fixup);
		if (ret < 0) {
			netdev_err(dev->net, "Failed to register fixup for PHY_LAN8835\n");
			return NULL;
		}
		/* add more external PHY fixup here if needed */

		phydev->is_internal = false;
	}
	return phydev;
}