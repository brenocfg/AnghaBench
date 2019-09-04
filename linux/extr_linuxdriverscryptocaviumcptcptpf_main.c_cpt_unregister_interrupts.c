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
struct cpt_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPT_PF_INT_VEC_E_MBOXX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct cpt_device*) ; 
 int /*<<< orphan*/  pci_disable_msix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpt_unregister_interrupts(struct cpt_device *cpt)
{
	free_irq(pci_irq_vector(cpt->pdev, CPT_PF_INT_VEC_E_MBOXX(0)), cpt);
	pci_disable_msix(cpt->pdev);
}