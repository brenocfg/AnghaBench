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
struct hfi1_ctxtdata {int /*<<< orphan*/  dd; int /*<<< orphan*/  flags; int /*<<< orphan*/  jkey; scalar_t__ rcvhdrtail_kvaddr; scalar_t__ urgent_poll; scalar_t__ urgent; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_RTAIL ; 
 int /*<<< orphan*/  HDRSUPP ; 
 scalar_t__ HFI1_CAP_UGET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int HFI1_RCVCTRL_CTXT_ENB ; 
 unsigned int HFI1_RCVCTRL_NO_EGR_DROP_ENB ; 
 unsigned int HFI1_RCVCTRL_NO_RHQ_DROP_ENB ; 
 unsigned int HFI1_RCVCTRL_ONE_PKT_EGR_ENB ; 
 unsigned int HFI1_RCVCTRL_TAILUPD_DIS ; 
 unsigned int HFI1_RCVCTRL_TAILUPD_ENB ; 
 unsigned int HFI1_RCVCTRL_TIDFLOW_ENB ; 
 unsigned int HFI1_RCVCTRL_URGENT_ENB ; 
 int /*<<< orphan*/  MULTI_PKT_EGR ; 
 int /*<<< orphan*/  NODROP_EGR_FULL ; 
 int /*<<< orphan*/  NODROP_RHQ_FULL ; 
 int /*<<< orphan*/  clear_rcvhdrtail (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_rcvctrl (int /*<<< orphan*/ ,unsigned int,struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  hfi1_set_ctxt_jkey (int /*<<< orphan*/ ,struct hfi1_ctxtdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void user_init(struct hfi1_ctxtdata *uctxt)
{
	unsigned int rcvctrl_ops = 0;

	/* initialize poll variables... */
	uctxt->urgent = 0;
	uctxt->urgent_poll = 0;

	/*
	 * Now enable the ctxt for receive.
	 * For chips that are set to DMA the tail register to memory
	 * when they change (and when the update bit transitions from
	 * 0 to 1.  So for those chips, we turn it off and then back on.
	 * This will (very briefly) affect any other open ctxts, but the
	 * duration is very short, and therefore isn't an issue.  We
	 * explicitly set the in-memory tail copy to 0 beforehand, so we
	 * don't have to wait to be sure the DMA update has happened
	 * (chip resets head/tail to 0 on transition to enable).
	 */
	if (uctxt->rcvhdrtail_kvaddr)
		clear_rcvhdrtail(uctxt);

	/* Setup J_KEY before enabling the context */
	hfi1_set_ctxt_jkey(uctxt->dd, uctxt, uctxt->jkey);

	rcvctrl_ops = HFI1_RCVCTRL_CTXT_ENB;
	rcvctrl_ops |= HFI1_RCVCTRL_URGENT_ENB;
	if (HFI1_CAP_UGET_MASK(uctxt->flags, HDRSUPP))
		rcvctrl_ops |= HFI1_RCVCTRL_TIDFLOW_ENB;
	/*
	 * Ignore the bit in the flags for now until proper
	 * support for multiple packet per rcv array entry is
	 * added.
	 */
	if (!HFI1_CAP_UGET_MASK(uctxt->flags, MULTI_PKT_EGR))
		rcvctrl_ops |= HFI1_RCVCTRL_ONE_PKT_EGR_ENB;
	if (HFI1_CAP_UGET_MASK(uctxt->flags, NODROP_EGR_FULL))
		rcvctrl_ops |= HFI1_RCVCTRL_NO_EGR_DROP_ENB;
	if (HFI1_CAP_UGET_MASK(uctxt->flags, NODROP_RHQ_FULL))
		rcvctrl_ops |= HFI1_RCVCTRL_NO_RHQ_DROP_ENB;
	/*
	 * The RcvCtxtCtrl.TailUpd bit has to be explicitly written.
	 * We can't rely on the correct value to be set from prior
	 * uses of the chip or ctxt. Therefore, add the rcvctrl op
	 * for both cases.
	 */
	if (HFI1_CAP_UGET_MASK(uctxt->flags, DMA_RTAIL))
		rcvctrl_ops |= HFI1_RCVCTRL_TAILUPD_ENB;
	else
		rcvctrl_ops |= HFI1_RCVCTRL_TAILUPD_DIS;
	hfi1_rcvctrl(uctxt->dd, rcvctrl_ops, uctxt);
}