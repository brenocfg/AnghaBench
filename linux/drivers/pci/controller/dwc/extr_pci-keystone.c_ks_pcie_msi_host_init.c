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
struct pcie_port {int /*<<< orphan*/ * msi_irq_chip; } ;

/* Variables and functions */
 int dw_pcie_allocate_domains (struct pcie_port*) ; 
 int /*<<< orphan*/  ks_pcie_msi_irq_chip ; 

__attribute__((used)) static int ks_pcie_msi_host_init(struct pcie_port *pp)
{
	pp->msi_irq_chip = &ks_pcie_msi_irq_chip;
	return dw_pcie_allocate_domains(pp);
}