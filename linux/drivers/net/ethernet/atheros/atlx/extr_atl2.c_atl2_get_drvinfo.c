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
struct atl2_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 char* atl2_driver_name ; 
 char* atl2_driver_version ; 
 struct atl2_adapter* netdev_priv (struct net_device*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void atl2_get_drvinfo(struct net_device *netdev,
	struct ethtool_drvinfo *drvinfo)
{
	struct atl2_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver,  atl2_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, atl2_driver_version,
		sizeof(drvinfo->version));
	strlcpy(drvinfo->fw_version, "L2", sizeof(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		sizeof(drvinfo->bus_info));
}