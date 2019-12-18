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
struct ioc3_private {int /*<<< orphan*/  pdev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOC3_NAME ; 
 int /*<<< orphan*/  IOC3_VERSION ; 
 struct ioc3_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ioc3_get_drvinfo(struct net_device *dev,
			     struct ethtool_drvinfo *info)
{
	struct ioc3_private *ip = netdev_priv(dev);

	strlcpy(info->driver, IOC3_NAME, sizeof(info->driver));
	strlcpy(info->version, IOC3_VERSION, sizeof(info->version));
	strlcpy(info->bus_info, pci_name(ip->pdev), sizeof(info->bus_info));
}