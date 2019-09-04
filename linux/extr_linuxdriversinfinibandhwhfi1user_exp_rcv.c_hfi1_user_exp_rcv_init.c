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
typedef  int u16 ;
struct rb_node {int dummy; } ;
struct hfi1_filedata {int tid_limit; int subctxt; int /*<<< orphan*/  tid_lock; int /*<<< orphan*/  handler; int /*<<< orphan*/  mm; int /*<<< orphan*/ * entry_to_rb; void* invalid_tids; scalar_t__ invalid_tid_idx; int /*<<< orphan*/  invalid_lock; } ;
struct hfi1_devdata {TYPE_1__* pport; } ;
struct hfi1_ctxtdata {int expected_count; int subctxt_cnt; int /*<<< orphan*/  flags; struct hfi1_devdata* dd; } ;
struct TYPE_2__ {int /*<<< orphan*/  hfi1_wq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HFI1_CAP_UGET_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TID_UNMAP ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,int) ; 
 int hfi1_mmu_rb_register (struct hfi1_filedata*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tid_rb_ops ; 

int hfi1_user_exp_rcv_init(struct hfi1_filedata *fd,
			   struct hfi1_ctxtdata *uctxt)
{
	struct hfi1_devdata *dd = uctxt->dd;
	int ret = 0;

	spin_lock_init(&fd->tid_lock);
	spin_lock_init(&fd->invalid_lock);

	fd->entry_to_rb = kcalloc(uctxt->expected_count,
				  sizeof(struct rb_node *),
				  GFP_KERNEL);
	if (!fd->entry_to_rb)
		return -ENOMEM;

	if (!HFI1_CAP_UGET_MASK(uctxt->flags, TID_UNMAP)) {
		fd->invalid_tid_idx = 0;
		fd->invalid_tids = kcalloc(uctxt->expected_count,
					   sizeof(*fd->invalid_tids),
					   GFP_KERNEL);
		if (!fd->invalid_tids) {
			kfree(fd->entry_to_rb);
			fd->entry_to_rb = NULL;
			return -ENOMEM;
		}

		/*
		 * Register MMU notifier callbacks. If the registration
		 * fails, continue without TID caching for this context.
		 */
		ret = hfi1_mmu_rb_register(fd, fd->mm, &tid_rb_ops,
					   dd->pport->hfi1_wq,
					   &fd->handler);
		if (ret) {
			dd_dev_info(dd,
				    "Failed MMU notifier registration %d\n",
				    ret);
			ret = 0;
		}
	}

	/*
	 * PSM does not have a good way to separate, count, and
	 * effectively enforce a limit on RcvArray entries used by
	 * subctxts (when context sharing is used) when TID caching
	 * is enabled. To help with that, we calculate a per-process
	 * RcvArray entry share and enforce that.
	 * If TID caching is not in use, PSM deals with usage on its
	 * own. In that case, we allow any subctxt to take all of the
	 * entries.
	 *
	 * Make sure that we set the tid counts only after successful
	 * init.
	 */
	spin_lock(&fd->tid_lock);
	if (uctxt->subctxt_cnt && fd->handler) {
		u16 remainder;

		fd->tid_limit = uctxt->expected_count / uctxt->subctxt_cnt;
		remainder = uctxt->expected_count % uctxt->subctxt_cnt;
		if (remainder && fd->subctxt < remainder)
			fd->tid_limit++;
	} else {
		fd->tid_limit = uctxt->expected_count;
	}
	spin_unlock(&fd->tid_lock);

	return ret;
}