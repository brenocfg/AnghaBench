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
typedef  size_t u32 ;
struct kvm_task_sleep_node {size_t token; int halted; int /*<<< orphan*/  wq; int /*<<< orphan*/  link; int /*<<< orphan*/  cpu; } ;
struct kvm_task_sleep_head {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PREEMPT_COUNT ; 
 int /*<<< orphan*/  DECLARE_SWAITQUEUE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KVM_TASK_SLEEP_HASHBITS ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 struct kvm_task_sleep_node* _find_apf_task (struct kvm_task_sleep_head*,size_t) ; 
 struct kvm_task_sleep_head* async_pf_sleepers ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  finish_swait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t hash_32 (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_unhashed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_swait_queue_head (int /*<<< orphan*/ *) ; 
 scalar_t__ is_idle_task (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kvm_task_sleep_node*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  native_safe_halt () ; 
 int preempt_count () ; 
 int /*<<< orphan*/  prepare_to_swait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_irq_enter () ; 
 int /*<<< orphan*/  rcu_irq_exit () ; 
 scalar_t__ rcu_preempt_depth () ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  wait ; 

void kvm_async_pf_task_wait(u32 token, int interrupt_kernel)
{
	u32 key = hash_32(token, KVM_TASK_SLEEP_HASHBITS);
	struct kvm_task_sleep_head *b = &async_pf_sleepers[key];
	struct kvm_task_sleep_node n, *e;
	DECLARE_SWAITQUEUE(wait);

	rcu_irq_enter();

	raw_spin_lock(&b->lock);
	e = _find_apf_task(b, token);
	if (e) {
		/* dummy entry exist -> wake up was delivered ahead of PF */
		hlist_del(&e->link);
		kfree(e);
		raw_spin_unlock(&b->lock);

		rcu_irq_exit();
		return;
	}

	n.token = token;
	n.cpu = smp_processor_id();
	n.halted = is_idle_task(current) ||
		   (IS_ENABLED(CONFIG_PREEMPT_COUNT)
		    ? preempt_count() > 1 || rcu_preempt_depth()
		    : interrupt_kernel);
	init_swait_queue_head(&n.wq);
	hlist_add_head(&n.link, &b->list);
	raw_spin_unlock(&b->lock);

	for (;;) {
		if (!n.halted)
			prepare_to_swait_exclusive(&n.wq, &wait, TASK_UNINTERRUPTIBLE);
		if (hlist_unhashed(&n.link))
			break;

		rcu_irq_exit();

		if (!n.halted) {
			local_irq_enable();
			schedule();
			local_irq_disable();
		} else {
			/*
			 * We cannot reschedule. So halt.
			 */
			native_safe_halt();
			local_irq_disable();
		}

		rcu_irq_enter();
	}
	if (!n.halted)
		finish_swait(&n.wq, &wait);

	rcu_irq_exit();
	return;
}