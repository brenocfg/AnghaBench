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
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct cobalt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 

__attribute__((used)) static void cobalt_free_msi(struct cobalt *cobalt, struct pci_dev *pci_dev)
{
	free_irq(pci_dev->irq, (void *)cobalt);
	pci_free_irq_vectors(pci_dev);
}