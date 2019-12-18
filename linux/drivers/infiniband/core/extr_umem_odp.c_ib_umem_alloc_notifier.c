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
struct mmu_notifier {int dummy; } ;
struct mm_struct {int dummy; } ;
struct ib_ucontext_per_mm {struct mmu_notifier mn; int /*<<< orphan*/  tgid; int /*<<< orphan*/  umem_rwsem; int /*<<< orphan*/  umem_tree; } ;
struct TYPE_2__ {int /*<<< orphan*/  group_leader; struct mm_struct* mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct mmu_notifier* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIDTYPE_PID ; 
 int /*<<< orphan*/  RB_ROOT_CACHED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  get_task_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 struct ib_ucontext_per_mm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static struct mmu_notifier *ib_umem_alloc_notifier(struct mm_struct *mm)
{
	struct ib_ucontext_per_mm *per_mm;

	per_mm = kzalloc(sizeof(*per_mm), GFP_KERNEL);
	if (!per_mm)
		return ERR_PTR(-ENOMEM);

	per_mm->umem_tree = RB_ROOT_CACHED;
	init_rwsem(&per_mm->umem_rwsem);

	WARN_ON(mm != current->mm);
	rcu_read_lock();
	per_mm->tgid = get_task_pid(current->group_leader, PIDTYPE_PID);
	rcu_read_unlock();
	return &per_mm->mn;
}