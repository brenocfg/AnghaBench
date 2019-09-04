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
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct be_adapter {char* fw_ver; char* fw_on_flash; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 char* DRV_NAME ; 
 char* DRV_VER ; 
 int /*<<< orphan*/  FW_VER_LEN ; 
 int /*<<< orphan*/  memcmp (char*,char*,int /*<<< orphan*/ ) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void be_get_drvinfo(struct net_device *netdev,
			   struct ethtool_drvinfo *drvinfo)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, DRV_NAME, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, DRV_VER, sizeof(drvinfo->version));
	if (!memcmp(adapter->fw_ver, adapter->fw_on_flash, FW_VER_LEN))
		strlcpy(drvinfo->fw_version, adapter->fw_ver,
			sizeof(drvinfo->fw_version));
	else
		snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
			 "%s [%s]", adapter->fw_ver, adapter->fw_on_flash);

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		sizeof(drvinfo->bus_info));
}