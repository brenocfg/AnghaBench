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
struct e1000_adapter {int eeprom_vers; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000e_driver_name ; 
 int /*<<< orphan*/  e1000e_driver_version ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000_get_drvinfo(struct net_device *netdev,
			      struct ethtool_drvinfo *drvinfo)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);

	strlcpy(drvinfo->driver, e1000e_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, e1000e_driver_version,
		sizeof(drvinfo->version));

	/* EEPROM image version # is reported as firmware version # for
	 * PCI-E controllers
	 */
	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
		 "%d.%d-%d",
		 (adapter->eeprom_vers & 0xF000) >> 12,
		 (adapter->eeprom_vers & 0x0FF0) >> 4,
		 (adapter->eeprom_vers & 0x000F));

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		sizeof(drvinfo->bus_info));
}