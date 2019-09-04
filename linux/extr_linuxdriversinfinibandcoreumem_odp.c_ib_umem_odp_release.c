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
struct task_struct {int dummy; } ;
struct mm_struct {int dummy; } ;
struct ib_umem {struct ib_umem* odp_data; int /*<<< orphan*/  page_list; int /*<<< orphan*/  dma_list; int /*<<< orphan*/  notifier_completion; int /*<<< orphan*/  no_private_counters; int /*<<< orphan*/  mn_counters_active; int /*<<< orphan*/  interval_tree; struct ib_ucontext* context; } ;
struct ib_ucontext {int /*<<< orphan*/  umem_rwsem; int /*<<< orphan*/  mn; int /*<<< orphan*/  tgid; int /*<<< orphan*/  odp_mrs_count; int /*<<< orphan*/  umem_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 struct task_struct* get_pid_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 scalar_t__ ib_umem_end (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_odp_unmap_dma_pages (struct ib_umem*,scalar_t__,scalar_t__) ; 
 scalar_t__ ib_umem_start (struct ib_umem*) ; 
 int /*<<< orphan*/  kfree (struct ib_umem*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int /*<<< orphan*/  mmu_notifier_unregister (int /*<<< orphan*/ *,struct mm_struct*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  rbt_ib_umem_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

void ib_umem_odp_release(struct ib_umem *umem)
{
	struct ib_ucontext *context = umem->context;

	/*
	 * Ensure that no more pages are mapped in the umem.
	 *
	 * It is the driver's responsibility to ensure, before calling us,
	 * that the hardware will not attempt to access the MR any more.
	 */
	ib_umem_odp_unmap_dma_pages(umem, ib_umem_start(umem),
				    ib_umem_end(umem));

	down_write(&context->umem_rwsem);
	if (likely(ib_umem_start(umem) != ib_umem_end(umem)))
		rbt_ib_umem_remove(&umem->odp_data->interval_tree,
				   &context->umem_tree);
	context->odp_mrs_count--;
	if (!umem->odp_data->mn_counters_active) {
		list_del(&umem->odp_data->no_private_counters);
		complete_all(&umem->odp_data->notifier_completion);
	}

	/*
	 * Downgrade the lock to a read lock. This ensures that the notifiers
	 * (who lock the mutex for reading) will be able to finish, and we
	 * will be able to enventually obtain the mmu notifiers SRCU. Note
	 * that since we are doing it atomically, no other user could register
	 * and unregister while we do the check.
	 */
	downgrade_write(&context->umem_rwsem);
	if (!context->odp_mrs_count) {
		struct task_struct *owning_process = NULL;
		struct mm_struct *owning_mm        = NULL;

		owning_process = get_pid_task(context->tgid,
					      PIDTYPE_PID);
		if (owning_process == NULL)
			/*
			 * The process is already dead, notifier were removed
			 * already.
			 */
			goto out;

		owning_mm = get_task_mm(owning_process);
		if (owning_mm == NULL)
			/*
			 * The process' mm is already dead, notifier were
			 * removed already.
			 */
			goto out_put_task;
		mmu_notifier_unregister(&context->mn, owning_mm);

		mmput(owning_mm);

out_put_task:
		put_task_struct(owning_process);
	}
out:
	up_read(&context->umem_rwsem);

	vfree(umem->odp_data->dma_list);
	vfree(umem->odp_data->page_list);
	kfree(umem->odp_data);
	kfree(umem);
}