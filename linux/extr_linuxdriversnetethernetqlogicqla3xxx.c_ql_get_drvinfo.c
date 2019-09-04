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
struct ql3_adapter {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 struct ql3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql3xxx_driver_name ; 
 int /*<<< orphan*/  ql3xxx_driver_version ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ql_get_drvinfo(struct net_device *ndev,
			   struct ethtool_drvinfo *drvinfo)
{
	struct ql3_adapter *qdev = netdev_priv(ndev);
	strlcpy(drvinfo->driver, ql3xxx_driver_name, sizeof(drvinfo->driver));
	strlcpy(drvinfo->version, ql3xxx_driver_version,
		sizeof(drvinfo->version));
	strlcpy(drvinfo->bus_info, pci_name(qdev->pdev),
		sizeof(drvinfo->bus_info));
}