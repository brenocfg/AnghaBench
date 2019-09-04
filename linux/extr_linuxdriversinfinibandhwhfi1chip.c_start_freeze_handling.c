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
struct send_context {int flags; } ;
struct hfi1_pportdata {int /*<<< orphan*/  freeze_work; int /*<<< orphan*/  hfi1_wq; struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int num_send_contexts; TYPE_1__* send_contexts; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {struct send_context* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCE_CTRL ; 
 int /*<<< orphan*/  CCE_CTRL_SPC_FREEZE_SMASK ; 
 int FREEZE_ABORT ; 
 int FREEZE_LINK_DOWN ; 
 int FREEZE_SELF ; 
 int /*<<< orphan*/  HFI1_FROZEN ; 
 int SCF_ENABLED ; 
 int SCF_FROZEN ; 
 int SCF_HALTED ; 
 int SCF_LINK_DOWN ; 
 int /*<<< orphan*/  _HFI1_EVENT_FROZEN_BIT ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  hfi1_set_uevent_bits (struct hfi1_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc_stop (struct send_context*,int) ; 
 int /*<<< orphan*/  sdma_freeze_notify (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void start_freeze_handling(struct hfi1_pportdata *ppd, int flags)
{
	struct hfi1_devdata *dd = ppd->dd;
	struct send_context *sc;
	int i;
	int sc_flags;

	if (flags & FREEZE_SELF)
		write_csr(dd, CCE_CTRL, CCE_CTRL_SPC_FREEZE_SMASK);

	/* enter frozen mode */
	dd->flags |= HFI1_FROZEN;

	/* notify all SDMA engines that they are going into a freeze */
	sdma_freeze_notify(dd, !!(flags & FREEZE_LINK_DOWN));

	sc_flags = SCF_FROZEN | SCF_HALTED | (flags & FREEZE_LINK_DOWN ?
					      SCF_LINK_DOWN : 0);
	/* do halt pre-handling on all enabled send contexts */
	for (i = 0; i < dd->num_send_contexts; i++) {
		sc = dd->send_contexts[i].sc;
		if (sc && (sc->flags & SCF_ENABLED))
			sc_stop(sc, sc_flags);
	}

	/* Send context are frozen. Notify user space */
	hfi1_set_uevent_bits(ppd, _HFI1_EVENT_FROZEN_BIT);

	if (flags & FREEZE_ABORT) {
		dd_dev_err(dd,
			   "Aborted freeze recovery. Please REBOOT system\n");
		return;
	}
	/* queue non-interrupt handler */
	queue_work(ppd->hfi1_wq, &ppd->freeze_work);
}