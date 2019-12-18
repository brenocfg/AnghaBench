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
struct TYPE_2__ {int /*<<< orphan*/  owning_mm; } ;
struct ib_umem_odp {TYPE_1__ umem; int /*<<< orphan*/  notifier_completion; int /*<<< orphan*/  interval_tree; int /*<<< orphan*/  is_implicit_odp; int /*<<< orphan*/  page_list; int /*<<< orphan*/  dma_list; int /*<<< orphan*/  umem_mutex; struct ib_ucontext_per_mm* per_mm; } ;
struct ib_ucontext_per_mm {int /*<<< orphan*/  umem_rwsem; int /*<<< orphan*/  mn; int /*<<< orphan*/  umem_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_umem_end (struct ib_umem_odp*) ; 
 int /*<<< orphan*/  ib_umem_odp_unmap_dma_pages (struct ib_umem_odp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_start (struct ib_umem_odp*) ; 
 int /*<<< orphan*/  interval_tree_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_umem_odp*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmdrop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_notifier_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void ib_umem_odp_release(struct ib_umem_odp *umem_odp)
{
	struct ib_ucontext_per_mm *per_mm = umem_odp->per_mm;

	/*
	 * Ensure that no more pages are mapped in the umem.
	 *
	 * It is the driver's responsibility to ensure, before calling us,
	 * that the hardware will not attempt to access the MR any more.
	 */
	if (!umem_odp->is_implicit_odp) {
		mutex_lock(&umem_odp->umem_mutex);
		ib_umem_odp_unmap_dma_pages(umem_odp, ib_umem_start(umem_odp),
					    ib_umem_end(umem_odp));
		mutex_unlock(&umem_odp->umem_mutex);
		kvfree(umem_odp->dma_list);
		kvfree(umem_odp->page_list);
	}

	down_write(&per_mm->umem_rwsem);
	if (!umem_odp->is_implicit_odp) {
		interval_tree_remove(&umem_odp->interval_tree,
				     &per_mm->umem_tree);
		complete_all(&umem_odp->notifier_completion);
	}
	/*
	 * NOTE! mmu_notifier_unregister() can happen between a start/end
	 * callback, resulting in a missing end, and thus an unbalanced
	 * lock. This doesn't really matter to us since we are about to kfree
	 * the memory that holds the lock, however LOCKDEP doesn't like this.
	 * Thus we call the mmu_notifier_put under the rwsem and test the
	 * internal users count to reliably see if we are past this point.
	 */
	mmu_notifier_put(&per_mm->mn);
	up_write(&per_mm->umem_rwsem);

	mmdrop(umem_odp->umem.owning_mm);
	kfree(umem_odp);
}