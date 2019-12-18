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
struct mediatek_dwmac_plat_data {int rmii_rxc; int phy_mode; int /*<<< orphan*/  peri_regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PERI_ETH_PHY_INTF_SEL ; 
#define  PHY_INTERFACE_MODE_MII 133 
#define  PHY_INTERFACE_MODE_RGMII 132 
#define  PHY_INTERFACE_MODE_RGMII_ID 131 
#define  PHY_INTERFACE_MODE_RGMII_RXID 130 
#define  PHY_INTERFACE_MODE_RGMII_TXID 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int PHY_INTF_MII ; 
 int PHY_INTF_RGMII ; 
 int PHY_INTF_RMII ; 
 int RMII_CLK_SRC_RXC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt2712_set_interface(struct mediatek_dwmac_plat_data *plat)
{
	int rmii_rxc = plat->rmii_rxc ? RMII_CLK_SRC_RXC : 0;
	u32 intf_val = 0;

	/* select phy interface in top control domain */
	switch (plat->phy_mode) {
	case PHY_INTERFACE_MODE_MII:
		intf_val |= PHY_INTF_MII;
		break;
	case PHY_INTERFACE_MODE_RMII:
		intf_val |= (PHY_INTF_RMII | rmii_rxc);
		break;
	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_TXID:
	case PHY_INTERFACE_MODE_RGMII_RXID:
	case PHY_INTERFACE_MODE_RGMII_ID:
		intf_val |= PHY_INTF_RGMII;
		break;
	default:
		dev_err(plat->dev, "phy interface not supported\n");
		return -EINVAL;
	}

	regmap_write(plat->peri_regmap, PERI_ETH_PHY_INTF_SEL, intf_val);

	return 0;
}