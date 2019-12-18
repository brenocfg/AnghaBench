#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pcie_port {TYPE_1__* ops; int /*<<< orphan*/  root_bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  msi_host_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  dw_pcie_free_msi (struct pcie_port*) ; 
 scalar_t__ pci_msi_enabled () ; 
 int /*<<< orphan*/  pci_remove_root_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_stop_root_bus (int /*<<< orphan*/ ) ; 

void dw_pcie_host_deinit(struct pcie_port *pp)
{
	pci_stop_root_bus(pp->root_bus);
	pci_remove_root_bus(pp->root_bus);
	if (pci_msi_enabled() && !pp->ops->msi_host_init)
		dw_pcie_free_msi(pp);
}