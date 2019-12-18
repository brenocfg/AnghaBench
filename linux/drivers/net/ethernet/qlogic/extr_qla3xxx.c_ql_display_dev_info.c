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
struct ql3_adapter {scalar_t__ device_id; int pci_width; char* mem_map_registers; scalar_t__ pci_x; int /*<<< orphan*/  flags; int /*<<< orphan*/  pci_slot; int /*<<< orphan*/  chip_rev_id; int /*<<< orphan*/  index; struct pci_dev* pdev; } ;
struct pci_dev {char* irq; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 scalar_t__ QL3032_DEVICE_ID ; 
 int /*<<< orphan*/  QL_LINK_OPTICAL ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*,...) ; 
 struct ql3_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_info (struct ql3_adapter*,int /*<<< orphan*/ ,struct net_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ql_display_dev_info(struct net_device *ndev)
{
	struct ql3_adapter *qdev = netdev_priv(ndev);
	struct pci_dev *pdev = qdev->pdev;

	netdev_info(ndev,
		    "%s Adapter %d RevisionID %d found %s on PCI slot %d\n",
		    DRV_NAME, qdev->index, qdev->chip_rev_id,
		    qdev->device_id == QL3032_DEVICE_ID ? "QLA3032" : "QLA3022",
		    qdev->pci_slot);
	netdev_info(ndev, "%s Interface\n",
		test_bit(QL_LINK_OPTICAL, &qdev->flags) ? "OPTICAL" : "COPPER");

	/*
	 * Print PCI bus width/type.
	 */
	netdev_info(ndev, "Bus interface is %s %s\n",
		    ((qdev->pci_width == 64) ? "64-bit" : "32-bit"),
		    ((qdev->pci_x) ? "PCI-X" : "PCI"));

	netdev_info(ndev, "mem  IO base address adjusted = 0x%p\n",
		    qdev->mem_map_registers);
	netdev_info(ndev, "Interrupt number = %d\n", pdev->irq);

	netif_info(qdev, probe, ndev, "MAC address %pM\n", ndev->dev_addr);
}