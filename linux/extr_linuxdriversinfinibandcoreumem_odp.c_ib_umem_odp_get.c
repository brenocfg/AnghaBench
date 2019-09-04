#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct pid {int dummy; } ;
struct mm_struct {int /*<<< orphan*/  mmap_sem; } ;
struct ib_umem {int hugetlb; TYPE_2__* odp_data; int /*<<< orphan*/  page_shift; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  hlist; } ;
struct ib_ucontext {int odp_mrs_count; int /*<<< orphan*/  umem_rwsem; TYPE_1__ mn; int /*<<< orphan*/  notifier_count; int /*<<< orphan*/  no_private_counters; int /*<<< orphan*/  umem_tree; struct pid* tgid; } ;
struct hstate {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  group_leader; } ;
struct TYPE_7__ {int mn_counters_active; void* page_list; void* dma_list; int /*<<< orphan*/  no_private_counters; int /*<<< orphan*/  interval_tree; int /*<<< orphan*/  notifier_completion; int /*<<< orphan*/  umem_mutex; struct ib_umem* umem; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_ACCESS_HUGETLB ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  array_size (int,scalar_t__) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  downgrade_write (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (struct mm_struct*,scalar_t__) ; 
 struct mm_struct* get_task_mm (TYPE_4__*) ; 
 struct pid* get_task_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hstate* hstate_vma (struct vm_area_struct*) ; 
 int /*<<< orphan*/  huge_page_shift (struct hstate*) ; 
 scalar_t__ ib_umem_end (struct ib_umem*) ; 
 int /*<<< orphan*/  ib_umem_notifiers ; 
 scalar_t__ ib_umem_num_pages (struct ib_umem*) ; 
 scalar_t__ ib_umem_start (struct ib_umem*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_off () ; 
 int /*<<< orphan*/  lockdep_on () ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 int mmu_notifier_register (TYPE_1__*,struct mm_struct*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int /*<<< orphan*/  rbt_ib_umem_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vzalloc (int /*<<< orphan*/ ) ; 

int ib_umem_odp_get(struct ib_ucontext *context, struct ib_umem *umem,
		    int access)
{
	int ret_val;
	struct pid *our_pid;
	struct mm_struct *mm = get_task_mm(current);

	if (!mm)
		return -EINVAL;

	if (access & IB_ACCESS_HUGETLB) {
		struct vm_area_struct *vma;
		struct hstate *h;

		down_read(&mm->mmap_sem);
		vma = find_vma(mm, ib_umem_start(umem));
		if (!vma || !is_vm_hugetlb_page(vma)) {
			up_read(&mm->mmap_sem);
			return -EINVAL;
		}
		h = hstate_vma(vma);
		umem->page_shift = huge_page_shift(h);
		up_read(&mm->mmap_sem);
		umem->hugetlb = 1;
	} else {
		umem->hugetlb = 0;
	}

	/* Prevent creating ODP MRs in child processes */
	rcu_read_lock();
	our_pid = get_task_pid(current->group_leader, PIDTYPE_PID);
	rcu_read_unlock();
	put_pid(our_pid);
	if (context->tgid != our_pid) {
		ret_val = -EINVAL;
		goto out_mm;
	}

	umem->odp_data = kzalloc(sizeof(*umem->odp_data), GFP_KERNEL);
	if (!umem->odp_data) {
		ret_val = -ENOMEM;
		goto out_mm;
	}
	umem->odp_data->umem = umem;

	mutex_init(&umem->odp_data->umem_mutex);

	init_completion(&umem->odp_data->notifier_completion);

	if (ib_umem_num_pages(umem)) {
		umem->odp_data->page_list =
			vzalloc(array_size(sizeof(*umem->odp_data->page_list),
					   ib_umem_num_pages(umem)));
		if (!umem->odp_data->page_list) {
			ret_val = -ENOMEM;
			goto out_odp_data;
		}

		umem->odp_data->dma_list =
			vzalloc(array_size(sizeof(*umem->odp_data->dma_list),
					   ib_umem_num_pages(umem)));
		if (!umem->odp_data->dma_list) {
			ret_val = -ENOMEM;
			goto out_page_list;
		}
	}

	/*
	 * When using MMU notifiers, we will get a
	 * notification before the "current" task (and MM) is
	 * destroyed. We use the umem_rwsem semaphore to synchronize.
	 */
	down_write(&context->umem_rwsem);
	context->odp_mrs_count++;
	if (likely(ib_umem_start(umem) != ib_umem_end(umem)))
		rbt_ib_umem_insert(&umem->odp_data->interval_tree,
				   &context->umem_tree);
	if (likely(!atomic_read(&context->notifier_count)) ||
	    context->odp_mrs_count == 1)
		umem->odp_data->mn_counters_active = true;
	else
		list_add(&umem->odp_data->no_private_counters,
			 &context->no_private_counters);
	downgrade_write(&context->umem_rwsem);

	if (context->odp_mrs_count == 1) {
		/*
		 * Note that at this point, no MMU notifier is running
		 * for this context!
		 */
		atomic_set(&context->notifier_count, 0);
		INIT_HLIST_NODE(&context->mn.hlist);
		context->mn.ops = &ib_umem_notifiers;
		/*
		 * Lock-dep detects a false positive for mmap_sem vs.
		 * umem_rwsem, due to not grasping downgrade_write correctly.
		 */
		lockdep_off();
		ret_val = mmu_notifier_register(&context->mn, mm);
		lockdep_on();
		if (ret_val) {
			pr_err("Failed to register mmu_notifier %d\n", ret_val);
			ret_val = -EBUSY;
			goto out_mutex;
		}
	}

	up_read(&context->umem_rwsem);

	/*
	 * Note that doing an mmput can cause a notifier for the relevant mm.
	 * If the notifier is called while we hold the umem_rwsem, this will
	 * cause a deadlock. Therefore, we release the reference only after we
	 * released the semaphore.
	 */
	mmput(mm);
	return 0;

out_mutex:
	up_read(&context->umem_rwsem);
	vfree(umem->odp_data->dma_list);
out_page_list:
	vfree(umem->odp_data->page_list);
out_odp_data:
	kfree(umem->odp_data);
out_mm:
	mmput(mm);
	return ret_val;
}