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
struct genwqe_dev {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_irq_vectors (int /*<<< orphan*/ ) ; 

void genwqe_reset_interrupt_capability(struct genwqe_dev *cd)
{
	pci_free_irq_vectors(cd->pci_dev);
}