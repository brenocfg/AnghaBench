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
struct xge_pdata {struct platform_device* pdev; } ;
struct platform_device {char* name; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_FWVERS_LEN ; 
 char* XGENE_ENET_V2_VERSION ; 
 struct xge_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void xge_get_drvinfo(struct net_device *ndev,
			    struct ethtool_drvinfo *info)
{
	struct xge_pdata *pdata = netdev_priv(ndev);
	struct platform_device *pdev = pdata->pdev;

	strcpy(info->driver, "xgene-enet-v2");
	strcpy(info->version, XGENE_ENET_V2_VERSION);
	snprintf(info->fw_version, ETHTOOL_FWVERS_LEN, "N/A");
	sprintf(info->bus_info, "%s", pdev->name);
}