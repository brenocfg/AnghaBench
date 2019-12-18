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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct hinic_rx_mode_work {int /*<<< orphan*/  work; } ;
struct hinic_dev {int /*<<< orphan*/  hwdev; int /*<<< orphan*/  workq; struct hinic_rx_mode_work rx_mode_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_MGMT_MSG_CMD_LINK_STATUS ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hinic_free_hwdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwdev_cb_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hinic_dev* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void hinic_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct hinic_dev *nic_dev = netdev_priv(netdev);
	struct hinic_rx_mode_work *rx_mode_work;

	unregister_netdev(netdev);

	hinic_hwdev_cb_unregister(nic_dev->hwdev,
				  HINIC_MGMT_MSG_CMD_LINK_STATUS);

	rx_mode_work = &nic_dev->rx_mode_work;
	cancel_work_sync(&rx_mode_work->work);

	pci_set_drvdata(pdev, NULL);

	destroy_workqueue(nic_dev->workq);

	hinic_free_hwdev(nic_dev->hwdev);

	free_netdev(netdev);

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	dev_info(&pdev->dev, "HiNIC driver - removed\n");
}