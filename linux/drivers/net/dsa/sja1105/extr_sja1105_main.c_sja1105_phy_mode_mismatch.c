#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sja1105_xmii_params_entry {int /*<<< orphan*/ * xmii_mode; } ;
struct TYPE_4__ {TYPE_1__* tables; } ;
struct sja1105_private {TYPE_2__ static_config; } ;
typedef  int /*<<< orphan*/  sja1105_phy_interface_t ;
typedef  int phy_interface_t ;
struct TYPE_3__ {struct sja1105_xmii_params_entry* entries; } ;

/* Variables and functions */
 size_t BLK_IDX_XMII_PARAMS ; 
#define  PHY_INTERFACE_MODE_MII 133 
#define  PHY_INTERFACE_MODE_RGMII 132 
#define  PHY_INTERFACE_MODE_RGMII_ID 131 
#define  PHY_INTERFACE_MODE_RGMII_RXID 130 
#define  PHY_INTERFACE_MODE_RGMII_TXID 129 
#define  PHY_INTERFACE_MODE_RMII 128 
 int /*<<< orphan*/  XMII_MODE_MII ; 
 int /*<<< orphan*/  XMII_MODE_RGMII ; 
 int /*<<< orphan*/  XMII_MODE_RMII ; 

__attribute__((used)) static bool sja1105_phy_mode_mismatch(struct sja1105_private *priv, int port,
				      phy_interface_t interface)
{
	struct sja1105_xmii_params_entry *mii;
	sja1105_phy_interface_t phy_mode;

	mii = priv->static_config.tables[BLK_IDX_XMII_PARAMS].entries;
	phy_mode = mii->xmii_mode[port];

	switch (interface) {
	case PHY_INTERFACE_MODE_MII:
		return (phy_mode != XMII_MODE_MII);
	case PHY_INTERFACE_MODE_RMII:
		return (phy_mode != XMII_MODE_RMII);
	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_ID:
	case PHY_INTERFACE_MODE_RGMII_RXID:
	case PHY_INTERFACE_MODE_RGMII_TXID:
		return (phy_mode != XMII_MODE_RGMII);
	default:
		return true;
	}
}