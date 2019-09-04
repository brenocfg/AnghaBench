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
struct skge_port {scalar_t__ wol; } ;
struct skge_hw {int ports; struct net_device** dev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 
 int /*<<< orphan*/  device_may_wakeup (int /*<<< orphan*/ *) ; 
 struct skge_port* netdev_priv (struct net_device*) ; 
 struct skge_hw* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_wake_from_d3 (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skge_wol_init (struct skge_port*) ; 

__attribute__((used)) static void skge_shutdown(struct pci_dev *pdev)
{
	struct skge_hw *hw  = pci_get_drvdata(pdev);
	int i;

	if (!hw)
		return;

	for (i = 0; i < hw->ports; i++) {
		struct net_device *dev = hw->dev[i];
		struct skge_port *skge = netdev_priv(dev);

		if (skge->wol)
			skge_wol_init(skge);
	}

	pci_wake_from_d3(pdev, device_may_wakeup(&pdev->dev));
	pci_set_power_state(pdev, PCI_D3hot);
}