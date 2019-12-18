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
struct pci_bridge_emul {int /*<<< orphan*/  pci_regs_behavior; int /*<<< orphan*/  pcie_cap_regs_behavior; scalar_t__ has_pcie; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void pci_bridge_emul_cleanup(struct pci_bridge_emul *bridge)
{
	if (bridge->has_pcie)
		kfree(bridge->pcie_cap_regs_behavior);
	kfree(bridge->pci_regs_behavior);
}