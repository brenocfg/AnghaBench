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
struct platform_device {int dummy; } ;
struct pci_host_bridge {int /*<<< orphan*/  bus; } ;
struct altera_pcie {int /*<<< orphan*/  resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  altera_pcie_irq_teardown (struct altera_pcie*) ; 
 int /*<<< orphan*/  pci_free_resource_list (int /*<<< orphan*/ *) ; 
 struct pci_host_bridge* pci_host_bridge_from_priv (struct altera_pcie*) ; 
 int /*<<< orphan*/  pci_remove_root_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_stop_root_bus (int /*<<< orphan*/ ) ; 
 struct altera_pcie* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int altera_pcie_remove(struct platform_device *pdev)
{
	struct altera_pcie *pcie = platform_get_drvdata(pdev);
	struct pci_host_bridge *bridge = pci_host_bridge_from_priv(pcie);

	pci_stop_root_bus(bridge->bus);
	pci_remove_root_bus(bridge->bus);
	pci_free_resource_list(&pcie->resources);
	altera_pcie_irq_teardown(pcie);

	return 0;
}