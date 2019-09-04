#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct binder_proc {TYPE_1__* context; int /*<<< orphan*/  inner_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  entry; } ;
struct binder_node {scalar_t__ internal_strong_refs; TYPE_2__ work; int /*<<< orphan*/  debug_id; int /*<<< orphan*/  has_weak_ref; int /*<<< orphan*/  local_weak_refs; scalar_t__ has_strong_ref; int /*<<< orphan*/  local_strong_refs; struct binder_proc* proc; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {struct binder_node* binder_context_mgr_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_dequeue_work_ilocked (TYPE_2__*) ; 
 int /*<<< orphan*/  binder_enqueue_work_ilocked (TYPE_2__*,struct list_head*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int binder_inc_node_nilocked(struct binder_node *node, int strong,
				    int internal,
				    struct list_head *target_list)
{
	struct binder_proc *proc = node->proc;

	assert_spin_locked(&node->lock);
	if (proc)
		assert_spin_locked(&proc->inner_lock);
	if (strong) {
		if (internal) {
			if (target_list == NULL &&
			    node->internal_strong_refs == 0 &&
			    !(node->proc &&
			      node == node->proc->context->binder_context_mgr_node &&
			      node->has_strong_ref)) {
				pr_err("invalid inc strong node for %d\n",
					node->debug_id);
				return -EINVAL;
			}
			node->internal_strong_refs++;
		} else
			node->local_strong_refs++;
		if (!node->has_strong_ref && target_list) {
			binder_dequeue_work_ilocked(&node->work);
			/*
			 * Note: this function is the only place where we queue
			 * directly to a thread->todo without using the
			 * corresponding binder_enqueue_thread_work() helper
			 * functions; in this case it's ok to not set the
			 * process_todo flag, since we know this node work will
			 * always be followed by other work that starts queue
			 * processing: in case of synchronous transactions, a
			 * BR_REPLY or BR_ERROR; in case of oneway
			 * transactions, a BR_TRANSACTION_COMPLETE.
			 */
			binder_enqueue_work_ilocked(&node->work, target_list);
		}
	} else {
		if (!internal)
			node->local_weak_refs++;
		if (!node->has_weak_ref && list_empty(&node->work.entry)) {
			if (target_list == NULL) {
				pr_err("invalid inc weak node for %d\n",
					node->debug_id);
				return -EINVAL;
			}
			/*
			 * See comment above
			 */
			binder_enqueue_work_ilocked(&node->work, target_list);
		}
	}
	return 0;
}