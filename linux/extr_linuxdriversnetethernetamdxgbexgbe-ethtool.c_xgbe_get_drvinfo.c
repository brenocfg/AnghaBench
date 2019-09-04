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
struct xgbe_hw_features {int /*<<< orphan*/  version; } ;
struct xgbe_prv_data {int /*<<< orphan*/  dev; struct xgbe_hw_features hw_feat; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVID ; 
 int /*<<< orphan*/  MAC_VR ; 
 int /*<<< orphan*/  SNPSVER ; 
 int /*<<< orphan*/  USERVER ; 
 int /*<<< orphan*/  XGBE_DRV_NAME ; 
 int /*<<< orphan*/  XGBE_DRV_VERSION ; 
 int XGMAC_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 struct xgbe_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgbe_get_drvinfo(struct net_device *netdev,
			     struct ethtool_drvinfo *drvinfo)
{
	struct xgbe_prv_data *pdata = netdev_priv(netdev);
	struct xgbe_hw_features *hw_feat = &pdata->hw_feat;

	strlcpy(drvinfo->driver, XGBE_DRV_NAME, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, XGBE_DRV_VERSION, sizeof(drvinfo->version));
	strlcpy(drvinfo->bus_info, dev_name(pdata->dev),
		sizeof(drvinfo->bus_info));
	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version), "%d.%d.%d",
		 XGMAC_GET_BITS(hw_feat->version, MAC_VR, USERVER),
		 XGMAC_GET_BITS(hw_feat->version, MAC_VR, DEVID),
		 XGMAC_GET_BITS(hw_feat->version, MAC_VR, SNPSVER));
}