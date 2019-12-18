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
struct pcie_port {scalar_t__ msi_page; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  msi_domain; scalar_t__ msi_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_set_handler_data (scalar_t__,int /*<<< orphan*/ *) ; 

void dw_pcie_free_msi(struct pcie_port *pp)
{
	if (pp->msi_irq) {
		irq_set_chained_handler(pp->msi_irq, NULL);
		irq_set_handler_data(pp->msi_irq, NULL);
	}

	irq_domain_remove(pp->msi_domain);
	irq_domain_remove(pp->irq_domain);

	if (pp->msi_page)
		__free_page(pp->msi_page);
}