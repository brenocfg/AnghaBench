#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union xhci_trb {int dummy; } xhci_trb ;
typedef  int u64 ;
typedef  int u32 ;
struct xhci_hcd {int xhc_state; int /*<<< orphan*/  lock; TYPE_3__* ir_set; TYPE_2__* event_ring; TYPE_1__* op_regs; } ;
struct usb_hcd {int /*<<< orphan*/  msi_enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  erst_dequeue; int /*<<< orphan*/  irq_pending; } ;
struct TYPE_5__ {union xhci_trb* dequeue; int /*<<< orphan*/  deq_seg; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int ERST_EHB ; 
 int ERST_PTR_MASK ; 
 int IMAN_IP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int STS_EINT ; 
 int STS_FATAL ; 
 int XHCI_STATE_DYING ; 
 int XHCI_STATE_HALTED ; 
 struct xhci_hcd* hcd_to_xhci (struct usb_hcd*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_dbg (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_halt (struct xhci_hcd*) ; 
 scalar_t__ xhci_handle_event (struct xhci_hcd*) ; 
 int /*<<< orphan*/  xhci_hc_died (struct xhci_hcd*) ; 
 int xhci_read_64 (struct xhci_hcd*,int /*<<< orphan*/ *) ; 
 scalar_t__ xhci_trb_virt_to_dma (int /*<<< orphan*/ ,union xhci_trb*) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 
 int /*<<< orphan*/  xhci_write_64 (struct xhci_hcd*,int,int /*<<< orphan*/ *) ; 

irqreturn_t xhci_irq(struct usb_hcd *hcd)
{
	struct xhci_hcd *xhci = hcd_to_xhci(hcd);
	union xhci_trb *event_ring_deq;
	irqreturn_t ret = IRQ_NONE;
	unsigned long flags;
	dma_addr_t deq;
	u64 temp_64;
	u32 status;

	spin_lock_irqsave(&xhci->lock, flags);
	/* Check if the xHC generated the interrupt, or the irq is shared */
	status = readl(&xhci->op_regs->status);
	if (status == ~(u32)0) {
		xhci_hc_died(xhci);
		ret = IRQ_HANDLED;
		goto out;
	}

	if (!(status & STS_EINT))
		goto out;

	if (status & STS_FATAL) {
		xhci_warn(xhci, "WARNING: Host System Error\n");
		xhci_halt(xhci);
		ret = IRQ_HANDLED;
		goto out;
	}

	/*
	 * Clear the op reg interrupt status first,
	 * so we can receive interrupts from other MSI-X interrupters.
	 * Write 1 to clear the interrupt status.
	 */
	status |= STS_EINT;
	writel(status, &xhci->op_regs->status);

	if (!hcd->msi_enabled) {
		u32 irq_pending;
		irq_pending = readl(&xhci->ir_set->irq_pending);
		irq_pending |= IMAN_IP;
		writel(irq_pending, &xhci->ir_set->irq_pending);
	}

	if (xhci->xhc_state & XHCI_STATE_DYING ||
	    xhci->xhc_state & XHCI_STATE_HALTED) {
		xhci_dbg(xhci, "xHCI dying, ignoring interrupt. "
				"Shouldn't IRQs be disabled?\n");
		/* Clear the event handler busy flag (RW1C);
		 * the event ring should be empty.
		 */
		temp_64 = xhci_read_64(xhci, &xhci->ir_set->erst_dequeue);
		xhci_write_64(xhci, temp_64 | ERST_EHB,
				&xhci->ir_set->erst_dequeue);
		ret = IRQ_HANDLED;
		goto out;
	}

	event_ring_deq = xhci->event_ring->dequeue;
	/* FIXME this should be a delayed service routine
	 * that clears the EHB.
	 */
	while (xhci_handle_event(xhci) > 0) {}

	temp_64 = xhci_read_64(xhci, &xhci->ir_set->erst_dequeue);
	/* If necessary, update the HW's version of the event ring deq ptr. */
	if (event_ring_deq != xhci->event_ring->dequeue) {
		deq = xhci_trb_virt_to_dma(xhci->event_ring->deq_seg,
				xhci->event_ring->dequeue);
		if (deq == 0)
			xhci_warn(xhci, "WARN something wrong with SW event "
					"ring dequeue ptr.\n");
		/* Update HC event ring dequeue pointer */
		temp_64 &= ERST_PTR_MASK;
		temp_64 |= ((u64) deq & (u64) ~ERST_PTR_MASK);
	}

	/* Clear the event handler busy flag (RW1C); event ring is empty. */
	temp_64 |= ERST_EHB;
	xhci_write_64(xhci, temp_64, &xhci->ir_set->erst_dequeue);
	ret = IRQ_HANDLED;

out:
	spin_unlock_irqrestore(&xhci->lock, flags);

	return ret;
}