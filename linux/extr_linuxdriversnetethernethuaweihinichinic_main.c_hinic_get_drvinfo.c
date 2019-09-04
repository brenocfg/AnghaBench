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
struct hinic_hwif {int /*<<< orphan*/  pdev; } ;
struct hinic_hwdev {struct hinic_hwif* hwif; } ;
struct hinic_dev {struct hinic_hwdev* hwdev; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_DRV_NAME ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hinic_get_drvinfo(struct net_device *netdev,
			      struct ethtool_drvinfo *info)
{
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	struct hinic_hwdev *hwdev = nic_dev->hwdev;
	struct hinic_hwif *hwif = hwdev->hwif;

	strlcpy(info->driver, HINIC_DRV_NAME, sizeof(info->driver));
	strlcpy(info->bus_info, pci_name(hwif->pdev), sizeof(info->bus_info));
}