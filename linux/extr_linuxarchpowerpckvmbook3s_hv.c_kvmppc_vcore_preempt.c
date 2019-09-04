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
struct preempted_vcore_list {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;
struct kvmppc_vcore {scalar_t__ num_threads; int /*<<< orphan*/  preempt_list; int /*<<< orphan*/  kvm; int /*<<< orphan*/  pcpu; int /*<<< orphan*/  vcore_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCORE_PREEMPT ; 
 int /*<<< orphan*/  kvmppc_core_start_stolen (struct kvmppc_vcore*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  preempted_vcores ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct preempted_vcore_list* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ threads_per_vcore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvmppc_vcore_preempt(struct kvmppc_vcore *vc)
{
	struct preempted_vcore_list *lp = this_cpu_ptr(&preempted_vcores);

	vc->vcore_state = VCORE_PREEMPT;
	vc->pcpu = smp_processor_id();
	if (vc->num_threads < threads_per_vcore(vc->kvm)) {
		spin_lock(&lp->lock);
		list_add_tail(&vc->preempt_list, &lp->list);
		spin_unlock(&lp->lock);
	}

	/* Start accumulating stolen time */
	kvmppc_core_start_stolen(vc);
}