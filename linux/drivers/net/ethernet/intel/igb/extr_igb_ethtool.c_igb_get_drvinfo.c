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
struct igb_adapter {int /*<<< orphan*/  pdev; int /*<<< orphan*/  fw_version; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  n_priv_flags; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGB_PRIV_FLAGS_STR_LEN ; 
 int /*<<< orphan*/  igb_driver_name ; 
 int /*<<< orphan*/  igb_driver_version ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void igb_get_drvinfo(struct net_device *netdev,
			    struct ethtool_drvinfo *drvinfo)
{
	struct igb_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver,  igb_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, igb_driver_version, sizeof(drvinfo->version));

	/* EEPROM image version # is reported as firmware version # for
	 * 82575 controllers
	 */
	strlcpy(drvinfo->fw_version, adapter->fw_version,
		sizeof(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		sizeof(drvinfo->bus_info));

	drvinfo->n_priv_flags = IGB_PRIV_FLAGS_STR_LEN;
}