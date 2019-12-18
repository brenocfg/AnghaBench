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
struct xgbe_prv_data {int /*<<< orphan*/  netdev; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {scalar_t__ port_mode; int /*<<< orphan*/  sfp_eeprom; scalar_t__ sfp_mod_absent; } ;
struct ethtool_modinfo {int /*<<< orphan*/  eeprom_len; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079_LEN ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472_LEN ; 
 scalar_t__ XGBE_PORT_MODE_SFP ; 
 scalar_t__ XGBE_SFP_DIAGS_SUPPORTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_phy_module_info(struct xgbe_prv_data *pdata,
				struct ethtool_modinfo *modinfo)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;

	if (phy_data->port_mode != XGBE_PORT_MODE_SFP)
		return -ENXIO;

	if (!netif_running(pdata->netdev))
		return -EIO;

	if (phy_data->sfp_mod_absent)
		return -EIO;

	if (XGBE_SFP_DIAGS_SUPPORTED(&phy_data->sfp_eeprom)) {
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
	} else {
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	}

	return 0;
}