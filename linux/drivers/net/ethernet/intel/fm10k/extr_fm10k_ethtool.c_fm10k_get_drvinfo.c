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
struct fm10k_intfc {int /*<<< orphan*/  pdev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_driver_name ; 
 int /*<<< orphan*/  fm10k_driver_version ; 
 struct fm10k_intfc* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fm10k_get_drvinfo(struct net_device *dev,
			      struct ethtool_drvinfo *info)
{
	struct fm10k_intfc *interface = netdev_priv(dev);

	strncpy(info->driver, fm10k_driver_name,
		sizeof(info->driver) - 1);
	strncpy(info->version, fm10k_driver_version,
		sizeof(info->version) - 1);
	strncpy(info->bus_info, pci_name(interface->pdev),
		sizeof(info->bus_info) - 1);
}