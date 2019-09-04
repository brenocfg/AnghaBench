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
struct kvm_task_sleep_node {size_t token; int /*<<< orphan*/  link; int /*<<< orphan*/  wq; int /*<<< orphan*/  cpu; } ;
struct kvm_task_sleep_head {int /*<<< orphan*/  lock; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  KVM_TASK_SLEEP_HASHBITS ; 
 struct kvm_task_sleep_node* _find_apf_task (struct kvm_task_sleep_head*,size_t) ; 
 int /*<<< orphan*/  apf_task_wake_all () ; 
 int /*<<< orphan*/  apf_task_wake_one (struct kvm_task_sleep_node*) ; 
 struct kvm_task_sleep_head* async_pf_sleepers ; 
 int /*<<< orphan*/  cpu_relax () ; 
 size_t hash_32 (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_swait_queue_head (int /*<<< orphan*/ *) ; 
 struct kvm_task_sleep_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void kvm_async_pf_task_wake(u32 token)
{
	u32 key = hash_32(token, KVM_TASK_SLEEP_HASHBITS);
	struct kvm_task_sleep_head *b = &async_pf_sleepers[key];
	struct kvm_task_sleep_node *n;

	if (token == ~0) {
		apf_task_wake_all();
		return;
	}

again:
	raw_spin_lock(&b->lock);
	n = _find_apf_task(b, token);
	if (!n) {
		/*
		 * async PF was not yet handled.
		 * Add dummy entry for the token.
		 */
		n = kzalloc(sizeof(*n), GFP_ATOMIC);
		if (!n) {
			/*
			 * Allocation failed! Busy wait while other cpu
			 * handles async PF.
			 */
			raw_spin_unlock(&b->lock);
			cpu_relax();
			goto again;
		}
		n->token = token;
		n->cpu = smp_processor_id();
		init_swait_queue_head(&n->wq);
		hlist_add_head(&n->link, &b->list);
	} else
		apf_task_wake_one(n);
	raw_spin_unlock(&b->lock);
	return;
}