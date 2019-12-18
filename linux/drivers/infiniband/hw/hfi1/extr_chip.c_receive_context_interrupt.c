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
struct hfi1_devdata {int /*<<< orphan*/ * int_counter; } ;
struct hfi1_ctxtdata {int (* do_interrupt ) (struct hfi1_ctxtdata*,int /*<<< orphan*/ ) ;struct hfi1_devdata* dd; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_WAKE_THREAD ; 
 int RCV_PKT_LIMIT ; 
 int /*<<< orphan*/  aspm_ctx_disable (struct hfi1_ctxtdata*) ; 
 int check_packet_present (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  clear_recv_intr (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  force_recv_intr (struct hfi1_ctxtdata*) ; 
 int stub1 (struct hfi1_ctxtdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_receive_interrupt (struct hfi1_devdata*,struct hfi1_ctxtdata*) ; 

irqreturn_t receive_context_interrupt(int irq, void *data)
{
	struct hfi1_ctxtdata *rcd = data;
	struct hfi1_devdata *dd = rcd->dd;
	int disposition;
	int present;

	trace_hfi1_receive_interrupt(dd, rcd);
	this_cpu_inc(*dd->int_counter);
	aspm_ctx_disable(rcd);

	/* receive interrupt remains blocked while processing packets */
	disposition = rcd->do_interrupt(rcd, 0);

	/*
	 * Too many packets were seen while processing packets in this
	 * IRQ handler.  Invoke the handler thread.  The receive interrupt
	 * remains blocked.
	 */
	if (disposition == RCV_PKT_LIMIT)
		return IRQ_WAKE_THREAD;

	/*
	 * The packet processor detected no more packets.  Clear the receive
	 * interrupt and recheck for a packet packet that may have arrived
	 * after the previous check and interrupt clear.  If a packet arrived,
	 * force another interrupt.
	 */
	clear_recv_intr(rcd);
	present = check_packet_present(rcd);
	if (present)
		force_recv_intr(rcd);

	return IRQ_HANDLED;
}