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
struct task_struct {int /*<<< orphan*/  group_leader; scalar_t__ mm; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;
struct kfd_process {scalar_t__ pasid; int /*<<< orphan*/  mutex; int /*<<< orphan*/  pqm; scalar_t__ mm; int /*<<< orphan*/  kfd_processes; int /*<<< orphan*/  lead_thread; TYPE_1__ mmu_notifier; int /*<<< orphan*/  is_32bit_user_mode; int /*<<< orphan*/  last_restore_timestamp; int /*<<< orphan*/  restore_work; int /*<<< orphan*/  eviction_work; int /*<<< orphan*/  per_device_data; int /*<<< orphan*/  ref; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct kfd_process* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evict_process_worker ; 
 int /*<<< orphan*/  get_jiffies_64 () ; 
 int /*<<< orphan*/  get_task_struct (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_add_rcu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,uintptr_t) ; 
 int /*<<< orphan*/  in_compat_syscall () ; 
 scalar_t__ kfd_alloc_process_doorbells (struct kfd_process*) ; 
 int /*<<< orphan*/  kfd_event_init_process (struct kfd_process*) ; 
 int /*<<< orphan*/  kfd_free_process_doorbells (struct kfd_process*) ; 
 int kfd_init_apertures (struct kfd_process*) ; 
 scalar_t__ kfd_pasid_alloc () ; 
 int /*<<< orphan*/  kfd_pasid_free (scalar_t__) ; 
 int /*<<< orphan*/  kfd_process_destroy_pdds (struct kfd_process*) ; 
 int /*<<< orphan*/  kfd_process_free_outstanding_kfd_bos (struct kfd_process*) ; 
 int /*<<< orphan*/  kfd_process_mmu_notifier_ops ; 
 int /*<<< orphan*/  kfd_processes_table ; 
 int /*<<< orphan*/  kfree (struct kfd_process*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct kfd_process* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mmu_notifier_register (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int pqm_init (int /*<<< orphan*/ *,struct kfd_process*) ; 
 int /*<<< orphan*/  pqm_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  restore_process_worker ; 

__attribute__((used)) static struct kfd_process *create_process(const struct task_struct *thread)
{
	struct kfd_process *process;
	int err = -ENOMEM;

	process = kzalloc(sizeof(*process), GFP_KERNEL);
	if (!process)
		goto err_alloc_process;

	kref_init(&process->ref);
	mutex_init(&process->mutex);
	process->mm = thread->mm;
	process->lead_thread = thread->group_leader;
	INIT_LIST_HEAD(&process->per_device_data);
	INIT_DELAYED_WORK(&process->eviction_work, evict_process_worker);
	INIT_DELAYED_WORK(&process->restore_work, restore_process_worker);
	process->last_restore_timestamp = get_jiffies_64();
	kfd_event_init_process(process);
	process->is_32bit_user_mode = in_compat_syscall();

	process->pasid = kfd_pasid_alloc();
	if (process->pasid == 0)
		goto err_alloc_pasid;

	if (kfd_alloc_process_doorbells(process) < 0)
		goto err_alloc_doorbells;

	err = pqm_init(&process->pqm, process);
	if (err != 0)
		goto err_process_pqm_init;

	/* init process apertures*/
	err = kfd_init_apertures(process);
	if (err != 0)
		goto err_init_apertures;

	/* Must be last, have to use release destruction after this */
	process->mmu_notifier.ops = &kfd_process_mmu_notifier_ops;
	err = mmu_notifier_register(&process->mmu_notifier, process->mm);
	if (err)
		goto err_register_notifier;

	get_task_struct(process->lead_thread);
	hash_add_rcu(kfd_processes_table, &process->kfd_processes,
			(uintptr_t)process->mm);

	return process;

err_register_notifier:
	kfd_process_free_outstanding_kfd_bos(process);
	kfd_process_destroy_pdds(process);
err_init_apertures:
	pqm_uninit(&process->pqm);
err_process_pqm_init:
	kfd_free_process_doorbells(process);
err_alloc_doorbells:
	kfd_pasid_free(process->pasid);
err_alloc_pasid:
	mutex_destroy(&process->mutex);
	kfree(process);
err_alloc_process:
	return ERR_PTR(err);
}