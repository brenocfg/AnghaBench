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
struct pvrdma_srq {size_t srq_handle; int /*<<< orphan*/  pdir; int /*<<< orphan*/  umem; int /*<<< orphan*/  free; int /*<<< orphan*/  refcnt; } ;
struct pvrdma_dev {int /*<<< orphan*/  num_srqs; int /*<<< orphan*/  srq_tbl_lock; int /*<<< orphan*/ ** srq_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvrdma_page_dir_cleanup (struct pvrdma_dev*,int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvrdma_free_srq(struct pvrdma_dev *dev, struct pvrdma_srq *srq)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->srq_tbl_lock, flags);
	dev->srq_tbl[srq->srq_handle] = NULL;
	spin_unlock_irqrestore(&dev->srq_tbl_lock, flags);

	if (refcount_dec_and_test(&srq->refcnt))
		complete(&srq->free);
	wait_for_completion(&srq->free);

	/* There is no support for kernel clients, so this is safe. */
	ib_umem_release(srq->umem);

	pvrdma_page_dir_cleanup(dev, &srq->pdir);

	atomic_dec(&dev->num_srqs);
}