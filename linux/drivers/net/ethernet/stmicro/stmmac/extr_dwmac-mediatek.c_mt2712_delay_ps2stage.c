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
struct mac_delay_struct {int tx_delay; int rx_delay; } ;
struct mediatek_dwmac_plat_data {int phy_mode; int /*<<< orphan*/  dev; struct mac_delay_struct mac_delay; } ;

/* Variables and functions */
#define  PHY_INTERFACE_MODE_MII 133 
#define  PHY_INTERFACE_MODE_RGMII 132 
#define  PHY_INTERFACE_MODE_RGMII_ID 131 
#define  PHY_INTERFACE_MODE_RGMII_RXID 130 
#define  PHY_INTERFACE_MODE_RGMII_TXID 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mt2712_delay_ps2stage(struct mediatek_dwmac_plat_data *plat)
{
	struct mac_delay_struct *mac_delay = &plat->mac_delay;

	switch (plat->phy_mode) {
	case PHY_INTERFACE_MODE_MII:
	case PHY_INTERFACE_MODE_RMII:
		/* 550ps per stage for MII/RMII */
		mac_delay->tx_delay /= 550;
		mac_delay->rx_delay /= 550;
		break;
	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_TXID:
	case PHY_INTERFACE_MODE_RGMII_RXID:
	case PHY_INTERFACE_MODE_RGMII_ID:
		/* 170ps per stage for RGMII */
		mac_delay->tx_delay /= 170;
		mac_delay->rx_delay /= 170;
		break;
	default:
		dev_err(plat->dev, "phy interface not supported\n");
		break;
	}
}