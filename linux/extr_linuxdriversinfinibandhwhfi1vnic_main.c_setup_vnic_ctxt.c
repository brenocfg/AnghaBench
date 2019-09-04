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
struct hfi1_devdata {int dummy; } ;
struct hfi1_ctxtdata {int /*<<< orphan*/  dd; int /*<<< orphan*/  flags; scalar_t__ rcvhdrtail_kvaddr; int /*<<< orphan*/ * do_interrupt; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RTAIL ; 
 scalar_t__ HFI1_CAP_KGET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int HFI1_RCVCTRL_CTXT_ENB ; 
 unsigned int HFI1_RCVCTRL_INTRAVAIL_ENB ; 
 unsigned int HFI1_RCVCTRL_NO_EGR_DROP_ENB ; 
 unsigned int HFI1_RCVCTRL_NO_RHQ_DROP_ENB ; 
 unsigned int HFI1_RCVCTRL_ONE_PKT_EGR_ENB ; 
 unsigned int HFI1_RCVCTRL_TAILUPD_ENB ; 
 int /*<<< orphan*/  MULTI_PKT_EGR ; 
 int /*<<< orphan*/  NODROP_EGR_FULL ; 
 int /*<<< orphan*/  NODROP_RHQ_FULL ; 
 int /*<<< orphan*/  clear_rcvhdrtail (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  handle_receive_interrupt ; 
 int hfi1_create_rcvhdrq (struct hfi1_devdata*,struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_rcvctrl (int /*<<< orphan*/ ,unsigned int,struct hfi1_ctxtdata*) ; 
 int hfi1_setup_eagerbufs (struct hfi1_ctxtdata*) ; 

__attribute__((used)) static int setup_vnic_ctxt(struct hfi1_devdata *dd, struct hfi1_ctxtdata *uctxt)
{
	unsigned int rcvctrl_ops = 0;
	int ret;

	uctxt->do_interrupt = &handle_receive_interrupt;

	/* Now allocate the RcvHdr queue and eager buffers. */
	ret = hfi1_create_rcvhdrq(dd, uctxt);
	if (ret)
		goto done;

	ret = hfi1_setup_eagerbufs(uctxt);
	if (ret)
		goto done;

	if (uctxt->rcvhdrtail_kvaddr)
		clear_rcvhdrtail(uctxt);

	rcvctrl_ops = HFI1_RCVCTRL_CTXT_ENB;
	rcvctrl_ops |= HFI1_RCVCTRL_INTRAVAIL_ENB;

	if (!HFI1_CAP_KGET_MASK(uctxt->flags, MULTI_PKT_EGR))
		rcvctrl_ops |= HFI1_RCVCTRL_ONE_PKT_EGR_ENB;
	if (HFI1_CAP_KGET_MASK(uctxt->flags, NODROP_EGR_FULL))
		rcvctrl_ops |= HFI1_RCVCTRL_NO_EGR_DROP_ENB;
	if (HFI1_CAP_KGET_MASK(uctxt->flags, NODROP_RHQ_FULL))
		rcvctrl_ops |= HFI1_RCVCTRL_NO_RHQ_DROP_ENB;
	if (HFI1_CAP_KGET_MASK(uctxt->flags, DMA_RTAIL))
		rcvctrl_ops |= HFI1_RCVCTRL_TAILUPD_ENB;

	hfi1_rcvctrl(uctxt->dd, rcvctrl_ops, uctxt);
done:
	return ret;
}