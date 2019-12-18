#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int version; } ;
struct xlgmac_pdata {int /*<<< orphan*/  dev; int /*<<< orphan*/  drv_ver; int /*<<< orphan*/  drv_name; TYPE_1__ hw_feat; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_VR_DEVID_LEN ; 
 int /*<<< orphan*/  MAC_VR_DEVID_POS ; 
 int /*<<< orphan*/  MAC_VR_SNPSVER_LEN ; 
 int /*<<< orphan*/  MAC_VR_SNPSVER_POS ; 
 int /*<<< orphan*/  MAC_VR_USERVER_LEN ; 
 int /*<<< orphan*/  MAC_VR_USERVER_POS ; 
 int XLGMAC_GET_REG_BITS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 struct xlgmac_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlgmac_ethtool_get_drvinfo(struct net_device *netdev,
				       struct ethtool_drvinfo *drvinfo)
{
	struct xlgmac_pdata *pdata = netdev_priv(netdev);
	u32 ver = pdata->hw_feat.version;
	u32 snpsver, devid, userver;

	strlcpy(drvinfo->driver, pdata->drv_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, pdata->drv_ver, sizeof(drvinfo->version));
	strlcpy(drvinfo->bus_info, dev_name(pdata->dev),
		sizeof(drvinfo->bus_info));
	/* S|SNPSVER: Synopsys-defined Version
	 * D|DEVID: Indicates the Device family
	 * U|USERVER: User-defined Version
	 */
	snpsver = XLGMAC_GET_REG_BITS(ver, MAC_VR_SNPSVER_POS,
				      MAC_VR_SNPSVER_LEN);
	devid = XLGMAC_GET_REG_BITS(ver, MAC_VR_DEVID_POS,
				    MAC_VR_DEVID_LEN);
	userver = XLGMAC_GET_REG_BITS(ver, MAC_VR_USERVER_POS,
				      MAC_VR_USERVER_LEN);
	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
		 "S.D.U: %x.%x.%x", snpsver, devid, userver);
}