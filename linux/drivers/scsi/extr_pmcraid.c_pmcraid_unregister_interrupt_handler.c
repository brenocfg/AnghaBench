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
struct pmcraid_instance {int num_hrrq; scalar_t__ interrupt_mode; int /*<<< orphan*/ * hrrq_vector; struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 

__attribute__((used)) static
void pmcraid_unregister_interrupt_handler(struct pmcraid_instance *pinstance)
{
	struct pci_dev *pdev = pinstance->pdev;
	int i;

	for (i = 0; i < pinstance->num_hrrq; i++)
		free_irq(pci_irq_vector(pdev, i), &pinstance->hrrq_vector[i]);

	pinstance->interrupt_mode = 0;
	pci_free_irq_vectors(pdev);
}