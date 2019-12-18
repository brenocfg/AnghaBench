#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hfi1_filedata {TYPE_2__* uctxt; TYPE_1__* dd; int /*<<< orphan*/  subctxt; int /*<<< orphan*/  rec_cpu_num; } ;
struct TYPE_5__ {int /*<<< orphan*/  in_use_ctxts; int /*<<< orphan*/  numa_id; int /*<<< orphan*/  event_flags; int /*<<< orphan*/  wait; } ;
struct TYPE_4__ {int /*<<< orphan*/  uctxt_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HFI1_CTXT_BASE_FAILED ; 
 int /*<<< orphan*/  HFI1_CTXT_BASE_UNINIT ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_get_proc_affinity (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_rcd_put (TYPE_2__*) ; 
 int init_user_ctxt (struct hfi1_filedata*,TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int complete_subctxt(struct hfi1_filedata *fd)
{
	int ret;
	unsigned long flags;

	/*
	 * sub-context info can only be set up after the base context
	 * has been completed.
	 */
	ret = wait_event_interruptible(
		fd->uctxt->wait,
		!test_bit(HFI1_CTXT_BASE_UNINIT, &fd->uctxt->event_flags));

	if (test_bit(HFI1_CTXT_BASE_FAILED, &fd->uctxt->event_flags))
		ret = -ENOMEM;

	/* Finish the sub-context init */
	if (!ret) {
		fd->rec_cpu_num = hfi1_get_proc_affinity(fd->uctxt->numa_id);
		ret = init_user_ctxt(fd, fd->uctxt);
	}

	if (ret) {
		spin_lock_irqsave(&fd->dd->uctxt_lock, flags);
		__clear_bit(fd->subctxt, fd->uctxt->in_use_ctxts);
		spin_unlock_irqrestore(&fd->dd->uctxt_lock, flags);
		hfi1_rcd_put(fd->uctxt);
		fd->uctxt = NULL;
	}

	return ret;
}