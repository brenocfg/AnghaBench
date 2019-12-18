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
struct rtl_fw {int /*<<< orphan*/  version; } ;
struct rtl8169_private {int /*<<< orphan*/  pci_dev; struct rtl_fw* rtl_fw; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  fw_version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  MODULENAME ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtl8169_get_drvinfo(struct net_device *dev,
				struct ethtool_drvinfo *info)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	struct rtl_fw *rtl_fw = tp->rtl_fw;

	strlcpy(info->driver, MODULENAME, sizeof(info->driver));
	strlcpy(info->bus_info, pci_name(tp->pci_dev), sizeof(info->bus_info));
	BUILD_BUG_ON(sizeof(info->fw_version) < sizeof(rtl_fw->version));
	if (rtl_fw)
		strlcpy(info->fw_version, rtl_fw->version,
			sizeof(info->fw_version));
}