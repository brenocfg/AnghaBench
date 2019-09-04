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
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct et131x_adapter {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  DRIVER_VERSION ; 
 struct et131x_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void et131x_get_drvinfo(struct net_device *netdev,
			       struct ethtool_drvinfo *info)
{
	struct et131x_adapter *adapter = netdev_priv(netdev);

	strlcpy(info->driver, DRIVER_NAME, sizeof(info->driver));
	strlcpy(info->version, DRIVER_VERSION, sizeof(info->version));
	strlcpy(info->bus_info, pci_name(adapter->pdev),
		sizeof(info->bus_info));
}