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
typedef  int u32 ;
struct netxen_adapter {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETXEN_FW_VERSION_MAJOR ; 
 int /*<<< orphan*/  NETXEN_FW_VERSION_MINOR ; 
 int /*<<< orphan*/  NETXEN_FW_VERSION_SUB ; 
 int /*<<< orphan*/  NETXEN_NIC_LINUX_VERSIONID ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 struct netxen_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netxen_nic_driver_name ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
netxen_nic_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *drvinfo)
{
	struct netxen_adapter *adapter = netdev_priv(dev);
	u32 fw_major = 0;
	u32 fw_minor = 0;
	u32 fw_build = 0;

	strlcpy(drvinfo->driver, netxen_nic_driver_name,
		sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, NETXEN_NIC_LINUX_VERSIONID,
		sizeof(drvinfo->version));
	fw_major = NXRD32(adapter, NETXEN_FW_VERSION_MAJOR);
	fw_minor = NXRD32(adapter, NETXEN_FW_VERSION_MINOR);
	fw_build = NXRD32(adapter, NETXEN_FW_VERSION_SUB);
	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
		"%d.%d.%d", fw_major, fw_minor, fw_build);

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		sizeof(drvinfo->bus_info));
}