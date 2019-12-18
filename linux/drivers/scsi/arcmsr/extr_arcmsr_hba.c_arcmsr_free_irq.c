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
struct pci_dev {int dummy; } ;
struct AdapterControlBlock {int vector_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct AdapterControlBlock*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 

__attribute__((used)) static void arcmsr_free_irq(struct pci_dev *pdev,
		struct AdapterControlBlock *acb)
{
	int i;

	for (i = 0; i < acb->vector_count; i++)
		free_irq(pci_irq_vector(pdev, i), acb);
	pci_free_irq_vectors(pdev);
}