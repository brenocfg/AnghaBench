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
struct pci_endpoint_test {struct pci_dev* pdev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 

__attribute__((used)) static void pci_endpoint_test_free_irq_vectors(struct pci_endpoint_test *test)
{
	struct pci_dev *pdev = test->pdev;

	pci_free_irq_vectors(pdev);
}