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
struct qlcnic_adapter {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  version; int /*<<< orphan*/  driver; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_FW_VERSION_MAJOR ; 
 int /*<<< orphan*/  QLCNIC_FW_VERSION_MINOR ; 
 int /*<<< orphan*/  QLCNIC_FW_VERSION_SUB ; 
 int /*<<< orphan*/  QLCNIC_LINUX_VERSIONID ; 
 int QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_driver_name ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
qlcnic_get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *drvinfo)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	u32 fw_major, fw_minor, fw_build;
	fw_major = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MAJOR);
	fw_minor = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_MINOR);
	fw_build = QLC_SHARED_REG_RD32(adapter, QLCNIC_FW_VERSION_SUB);
	snprintf(drvinfo->fw_version, sizeof(drvinfo->fw_version),
		"%d.%d.%d", fw_major, fw_minor, fw_build);

	strlcpy(drvinfo->bus_info, pci_name(adapter->pdev),
		sizeof(drvinfo->bus_info));
	strlcpy(drvinfo->driver, qlcnic_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, QLCNIC_LINUX_VERSIONID,
		sizeof(drvinfo->version));
}