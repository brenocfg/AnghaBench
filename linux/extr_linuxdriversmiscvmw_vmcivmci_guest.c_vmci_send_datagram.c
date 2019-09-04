#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmci_datagram {int dummy; } ;
struct TYPE_2__ {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ VMCI_DATA_OUT_ADDR ; 
 int /*<<< orphan*/  VMCI_DG_SIZE (struct vmci_datagram*) ; 
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_UNAVAILABLE ; 
 scalar_t__ VMCI_RESULT_LOW_ADDR ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite8_rep (scalar_t__,struct vmci_datagram*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* vmci_dev_g ; 
 int /*<<< orphan*/  vmci_dev_spinlock ; 

int vmci_send_datagram(struct vmci_datagram *dg)
{
	unsigned long flags;
	int result;

	/* Check args. */
	if (dg == NULL)
		return VMCI_ERROR_INVALID_ARGS;

	/*
	 * Need to acquire spinlock on the device because the datagram
	 * data may be spread over multiple pages and the monitor may
	 * interleave device user rpc calls from multiple
	 * VCPUs. Acquiring the spinlock precludes that
	 * possibility. Disabling interrupts to avoid incoming
	 * datagrams during a "rep out" and possibly landing up in
	 * this function.
	 */
	spin_lock_irqsave(&vmci_dev_spinlock, flags);

	if (vmci_dev_g) {
		iowrite8_rep(vmci_dev_g->iobase + VMCI_DATA_OUT_ADDR,
			     dg, VMCI_DG_SIZE(dg));
		result = ioread32(vmci_dev_g->iobase + VMCI_RESULT_LOW_ADDR);
	} else {
		result = VMCI_ERROR_UNAVAILABLE;
	}

	spin_unlock_irqrestore(&vmci_dev_spinlock, flags);

	return result;
}