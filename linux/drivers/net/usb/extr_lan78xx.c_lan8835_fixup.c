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
struct phy_device {int /*<<< orphan*/  attached_dev; } ;
struct lan78xx_net {int /*<<< orphan*/  interface; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_RGMII_ID ; 
 int MAC_RGMII_ID_TXC_DELAY_EN_ ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_RGMII_TXID ; 
 int /*<<< orphan*/  RGMII_TX_BYP_DLL ; 
 int lan78xx_write_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int) ; 
 struct lan78xx_net* netdev_priv (int /*<<< orphan*/ ) ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lan8835_fixup(struct phy_device *phydev)
{
	int buf;
	int ret;
	struct lan78xx_net *dev = netdev_priv(phydev->attached_dev);

	/* LED2/PME_N/IRQ_N/RGMII_ID pin to IRQ_N mode */
	buf = phy_read_mmd(phydev, MDIO_MMD_PCS, 0x8010);
	buf &= ~0x1800;
	buf |= 0x0800;
	phy_write_mmd(phydev, MDIO_MMD_PCS, 0x8010, buf);

	/* RGMII MAC TXC Delay Enable */
	ret = lan78xx_write_reg(dev, MAC_RGMII_ID,
				MAC_RGMII_ID_TXC_DELAY_EN_);

	/* RGMII TX DLL Tune Adjust */
	ret = lan78xx_write_reg(dev, RGMII_TX_BYP_DLL, 0x3D00);

	dev->interface = PHY_INTERFACE_MODE_RGMII_TXID;

	return 1;
}