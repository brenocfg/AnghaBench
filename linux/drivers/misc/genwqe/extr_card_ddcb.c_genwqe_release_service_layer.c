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
struct genwqe_dev {int /*<<< orphan*/  queue; int /*<<< orphan*/ * card_thread; struct pci_dev* pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ddcb_queue_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ddcb_queue (struct genwqe_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct genwqe_dev*) ; 
 int /*<<< orphan*/  genwqe_reset_interrupt_capability (struct genwqe_dev*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 

int genwqe_release_service_layer(struct genwqe_dev *cd)
{
	struct pci_dev *pci_dev = cd->pci_dev;

	if (!ddcb_queue_initialized(&cd->queue))
		return 1;

	free_irq(pci_dev->irq, cd);
	genwqe_reset_interrupt_capability(cd);

	if (cd->card_thread != NULL) {
		kthread_stop(cd->card_thread);
		cd->card_thread = NULL;
	}

	free_ddcb_queue(cd, &cd->queue);
	return 0;
}