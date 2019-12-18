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
struct hfi1_ctxtdata {int /*<<< orphan*/  (* do_interrupt ) (struct hfi1_ctxtdata*,int) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int check_packet_present (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  clear_recv_intr (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  force_recv_intr (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  stub1 (struct hfi1_ctxtdata*,int) ; 

irqreturn_t receive_context_thread(int irq, void *data)
{
	struct hfi1_ctxtdata *rcd = data;
	int present;

	/* receive interrupt is still blocked from the IRQ handler */
	(void)rcd->do_interrupt(rcd, 1);

	/*
	 * The packet processor will only return if it detected no more
	 * packets.  Hold IRQs here so we can safely clear the interrupt and
	 * recheck for a packet that may have arrived after the previous
	 * check and the interrupt clear.  If a packet arrived, force another
	 * interrupt.
	 */
	local_irq_disable();
	clear_recv_intr(rcd);
	present = check_packet_present(rcd);
	if (present)
		force_recv_intr(rcd);
	local_irq_enable();

	return IRQ_HANDLED;
}