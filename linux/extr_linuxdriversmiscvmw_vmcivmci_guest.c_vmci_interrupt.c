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
struct vmci_guest_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  bm_tasklet; int /*<<< orphan*/  datagram_tasklet; scalar_t__ iobase; scalar_t__ exclusive_vectors; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ VMCI_ICR_ADDR ; 
 unsigned int VMCI_ICR_DATAGRAM ; 
 unsigned int VMCI_ICR_NOTIFICATION ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,unsigned int) ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t vmci_interrupt(int irq, void *_dev)
{
	struct vmci_guest_device *dev = _dev;

	/*
	 * If we are using MSI-X with exclusive vectors then we simply schedule
	 * the datagram tasklet, since we know the interrupt was meant for us.
	 * Otherwise we must read the ICR to determine what to do.
	 */

	if (dev->exclusive_vectors) {
		tasklet_schedule(&dev->datagram_tasklet);
	} else {
		unsigned int icr;

		/* Acknowledge interrupt and determine what needs doing. */
		icr = ioread32(dev->iobase + VMCI_ICR_ADDR);
		if (icr == 0 || icr == ~0)
			return IRQ_NONE;

		if (icr & VMCI_ICR_DATAGRAM) {
			tasklet_schedule(&dev->datagram_tasklet);
			icr &= ~VMCI_ICR_DATAGRAM;
		}

		if (icr & VMCI_ICR_NOTIFICATION) {
			tasklet_schedule(&dev->bm_tasklet);
			icr &= ~VMCI_ICR_NOTIFICATION;
		}

		if (icr != 0)
			dev_warn(dev->dev,
				 "Ignoring unknown interrupt cause (%d)\n",
				 icr);
	}

	return IRQ_HANDLED;
}