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
typedef  scalar_t__ u32 ;
struct port_info {struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct adapter {int /*<<< orphan*/  pdev; int /*<<< orphan*/  stats_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  DRV_VERSION ; 
 int G_FW_VERSION_MAJOR (scalar_t__) ; 
 int G_FW_VERSION_MICRO (scalar_t__) ; 
 int G_FW_VERSION_MINOR (scalar_t__) ; 
 scalar_t__ G_FW_VERSION_TYPE (scalar_t__) ; 
 int G_TP_VERSION_MAJOR (scalar_t__) ; 
 int G_TP_VERSION_MICRO (scalar_t__) ; 
 int G_TP_VERSION_MINOR (scalar_t__) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t3_get_fw_version (struct adapter*,scalar_t__*) ; 
 int /*<<< orphan*/  t3_get_tp_version (struct adapter*,scalar_t__*) ; 

__attribute__((used)) static void get_drvinfo(struct net_device *dev, struct ethtool_drvinfo *info)
{
	struct port_info *pi = netdev_priv(dev);
	struct adapter *adapter = pi->adapter;
	u32 fw_vers = 0;
	u32 tp_vers = 0;

	spin_lock(&adapter->stats_lock);
	t3_get_fw_version(adapter, &fw_vers);
	t3_get_tp_version(adapter, &tp_vers);
	spin_unlock(&adapter->stats_lock);

	strlcpy(info->driver, DRV_NAME, sizeof(info->driver));
	strlcpy(info->version, DRV_VERSION, sizeof(info->version));
	strlcpy(info->bus_info, pci_name(adapter->pdev),
		sizeof(info->bus_info));
	if (fw_vers)
		snprintf(info->fw_version, sizeof(info->fw_version),
			 "%s %u.%u.%u TP %u.%u.%u",
			 G_FW_VERSION_TYPE(fw_vers) ? "T" : "N",
			 G_FW_VERSION_MAJOR(fw_vers),
			 G_FW_VERSION_MINOR(fw_vers),
			 G_FW_VERSION_MICRO(fw_vers),
			 G_TP_VERSION_MAJOR(tp_vers),
			 G_TP_VERSION_MINOR(tp_vers),
			 G_TP_VERSION_MICRO(tp_vers));
}