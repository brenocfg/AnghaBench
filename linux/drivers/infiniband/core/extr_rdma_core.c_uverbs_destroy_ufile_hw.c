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
struct ib_uverbs_file {int /*<<< orphan*/  ucontext_lock; int /*<<< orphan*/  hw_destroy_rwsem; int /*<<< orphan*/  uobjects; TYPE_1__* ucontext; } ;
typedef  enum rdma_remove_reason { ____Placeholder_rdma_remove_reason } rdma_remove_reason ;
struct TYPE_2__ {int closing; int cleanup_retryable; } ;

/* Variables and functions */
 int RDMA_REMOVE_CLOSE ; 
 scalar_t__ __uverbs_cleanup_ufile (struct ib_uverbs_file*,int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ufile_destroy_ucontext (struct ib_uverbs_file*,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void uverbs_destroy_ufile_hw(struct ib_uverbs_file *ufile,
			     enum rdma_remove_reason reason)
{
	if (reason == RDMA_REMOVE_CLOSE) {
		/*
		 * During destruction we might trigger something that
		 * synchronously calls release on any file descriptor. For
		 * this reason all paths that come from file_operations
		 * release must use try_lock. They can progress knowing that
		 * there is an ongoing uverbs_destroy_ufile_hw that will clean
		 * up the driver resources.
		 */
		if (!mutex_trylock(&ufile->ucontext_lock))
			return;

	} else {
		mutex_lock(&ufile->ucontext_lock);
	}

	down_write(&ufile->hw_destroy_rwsem);

	/*
	 * If a ucontext was never created then we can't have any uobjects to
	 * cleanup, nothing to do.
	 */
	if (!ufile->ucontext)
		goto done;

	ufile->ucontext->closing = true;
	ufile->ucontext->cleanup_retryable = true;
	while (!list_empty(&ufile->uobjects))
		if (__uverbs_cleanup_ufile(ufile, reason)) {
			/*
			 * No entry was cleaned-up successfully during this
			 * iteration
			 */
			break;
		}

	ufile->ucontext->cleanup_retryable = false;
	if (!list_empty(&ufile->uobjects))
		__uverbs_cleanup_ufile(ufile, reason);

	ufile_destroy_ucontext(ufile, reason);

done:
	up_write(&ufile->hw_destroy_rwsem);
	mutex_unlock(&ufile->ucontext_lock);
}