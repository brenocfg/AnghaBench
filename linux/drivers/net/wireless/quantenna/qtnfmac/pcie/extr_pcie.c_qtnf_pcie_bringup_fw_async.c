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
struct qtnf_pcie_bus_priv {struct pci_dev* pdev; } ;
struct qtnf_bus {int /*<<< orphan*/  fw_work; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct qtnf_pcie_bus_priv* get_bus_priv (struct qtnf_bus*) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qtnf_pcie_bringup_fw_async(struct qtnf_bus *bus)
{
	struct qtnf_pcie_bus_priv *priv = get_bus_priv(bus);
	struct pci_dev *pdev = priv->pdev;

	get_device(&pdev->dev);
	schedule_work(&bus->fw_work);
}