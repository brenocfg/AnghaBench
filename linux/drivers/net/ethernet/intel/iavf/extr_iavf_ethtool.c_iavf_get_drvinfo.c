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
struct iavf_adapter {int /*<<< orphan*/  pdev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  n_priv_flags; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IAVF_PRIV_FLAGS_STR_LEN ; 
 char* iavf_driver_name ; 
 char* iavf_driver_version ; 
 struct iavf_adapter* netdev_priv (struct net_device*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void iavf_get_drvinfo(struct net_device *netdev,
			     struct ethtool_drvinfo *drvinfo)
{
	struct iavf_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, iavf_driver_name, 32);
	strlcpy(drvinfo->version, iavf_driver_version, 32);
	strlcpy(drvinfo->fw_version, "N/A", 4);
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev), 32);
	drvinfo->n_priv_flags = IAVF_PRIV_FLAGS_STR_LEN;
}