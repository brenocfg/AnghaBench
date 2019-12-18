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
struct vmci_guest_device {int /*<<< orphan*/  bm_tasklet; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t vmci_interrupt_bm(int irq, void *_dev)
{
	struct vmci_guest_device *dev = _dev;

	/* For MSI-X we can just assume it was meant for us. */
	tasklet_schedule(&dev->bm_tasklet);

	return IRQ_HANDLED;
}