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
typedef  int u64 ;
struct hfi1_ctxtdata {int ctxt; int ireg; int imask; int msix_intr; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_RCVCTXT ; 
 int IS_RCVAVAIL_START ; 
 int msix_request_irq (int /*<<< orphan*/ ,struct hfi1_ctxtdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  receive_context_interrupt ; 
 int /*<<< orphan*/  receive_context_thread ; 
 int /*<<< orphan*/  remap_intr (int /*<<< orphan*/ ,int,int) ; 

int msix_request_rcd_irq(struct hfi1_ctxtdata *rcd)
{
	int nr;

	nr = msix_request_irq(rcd->dd, rcd, receive_context_interrupt,
			      receive_context_thread, rcd->ctxt, IRQ_RCVCTXT);
	if (nr < 0)
		return nr;

	/*
	 * Set the interrupt register and mask for this
	 * context's interrupt.
	 */
	rcd->ireg = (IS_RCVAVAIL_START + rcd->ctxt) / 64;
	rcd->imask = ((u64)1) << ((IS_RCVAVAIL_START + rcd->ctxt) % 64);
	rcd->msix_intr = nr;
	remap_intr(rcd->dd, IS_RCVAVAIL_START + rcd->ctxt, nr);

	return 0;
}