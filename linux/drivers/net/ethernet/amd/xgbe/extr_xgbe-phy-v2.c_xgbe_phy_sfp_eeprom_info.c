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
struct xgbe_sfp_eeprom {int /*<<< orphan*/ * extd; int /*<<< orphan*/ * base; } ;
struct xgbe_sfp_ascii {int dummy; } ;
struct xgbe_prv_data {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 size_t XGBE_SFP_BASE_VENDOR_NAME ; 
 size_t XGBE_SFP_BASE_VENDOR_NAME_LEN ; 
 size_t XGBE_SFP_BASE_VENDOR_PN ; 
 size_t XGBE_SFP_BASE_VENDOR_PN_LEN ; 
 size_t XGBE_SFP_BASE_VENDOR_REV ; 
 size_t XGBE_SFP_BASE_VENDOR_REV_LEN ; 
 size_t XGBE_SFP_BASE_VENDOR_SN ; 
 size_t XGBE_SFP_BASE_VENDOR_SN_LEN ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void xgbe_phy_sfp_eeprom_info(struct xgbe_prv_data *pdata,
				     struct xgbe_sfp_eeprom *sfp_eeprom)
{
	struct xgbe_sfp_ascii sfp_ascii;
	char *sfp_data = (char *)&sfp_ascii;

	netif_dbg(pdata, drv, pdata->netdev, "SFP detected:\n");
	memcpy(sfp_data, &sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_NAME],
	       XGBE_SFP_BASE_VENDOR_NAME_LEN);
	sfp_data[XGBE_SFP_BASE_VENDOR_NAME_LEN] = '\0';
	netif_dbg(pdata, drv, pdata->netdev, "  vendor:         %s\n",
		  sfp_data);

	memcpy(sfp_data, &sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_PN],
	       XGBE_SFP_BASE_VENDOR_PN_LEN);
	sfp_data[XGBE_SFP_BASE_VENDOR_PN_LEN] = '\0';
	netif_dbg(pdata, drv, pdata->netdev, "  part number:    %s\n",
		  sfp_data);

	memcpy(sfp_data, &sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_REV],
	       XGBE_SFP_BASE_VENDOR_REV_LEN);
	sfp_data[XGBE_SFP_BASE_VENDOR_REV_LEN] = '\0';
	netif_dbg(pdata, drv, pdata->netdev, "  revision level: %s\n",
		  sfp_data);

	memcpy(sfp_data, &sfp_eeprom->extd[XGBE_SFP_BASE_VENDOR_SN],
	       XGBE_SFP_BASE_VENDOR_SN_LEN);
	sfp_data[XGBE_SFP_BASE_VENDOR_SN_LEN] = '\0';
	netif_dbg(pdata, drv, pdata->netdev, "  serial number:  %s\n",
		  sfp_data);
}