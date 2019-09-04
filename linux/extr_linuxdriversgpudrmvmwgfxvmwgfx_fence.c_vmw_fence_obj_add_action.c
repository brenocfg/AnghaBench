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
struct list_head {int dummy; } ;
struct vmw_fence_obj {struct list_head seq_passed_actions; int /*<<< orphan*/  base; } ;
struct vmw_fence_manager {int goal_irq_on; int /*<<< orphan*/  goal_irq_mutex; int /*<<< orphan*/  dev_priv; int /*<<< orphan*/  lock; int /*<<< orphan*/ * pending_actions; } ;
struct vmw_fence_action {size_t type; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 scalar_t__ dma_fence_is_signaled_locked (int /*<<< orphan*/ *) ; 
 struct vmw_fence_manager* fman_from_fence (struct vmw_fence_obj*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int vmw_fence_goal_check_locked (struct vmw_fence_obj*) ; 
 int /*<<< orphan*/  vmw_fences_perform_actions (struct vmw_fence_manager*,struct list_head*) ; 
 int /*<<< orphan*/  vmw_fences_update (struct vmw_fence_manager*) ; 
 int /*<<< orphan*/  vmw_goal_waiter_add (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmw_fence_obj_add_action(struct vmw_fence_obj *fence,
			      struct vmw_fence_action *action)
{
	struct vmw_fence_manager *fman = fman_from_fence(fence);
	bool run_update = false;

	mutex_lock(&fman->goal_irq_mutex);
	spin_lock(&fman->lock);

	fman->pending_actions[action->type]++;
	if (dma_fence_is_signaled_locked(&fence->base)) {
		struct list_head action_list;

		INIT_LIST_HEAD(&action_list);
		list_add_tail(&action->head, &action_list);
		vmw_fences_perform_actions(fman, &action_list);
	} else {
		list_add_tail(&action->head, &fence->seq_passed_actions);

		/*
		 * This function may set fman::seqno_valid, so it must
		 * be run with the goal_irq_mutex held.
		 */
		run_update = vmw_fence_goal_check_locked(fence);
	}

	spin_unlock(&fman->lock);

	if (run_update) {
		if (!fman->goal_irq_on) {
			fman->goal_irq_on = true;
			vmw_goal_waiter_add(fman->dev_priv);
		}
		vmw_fences_update(fman);
	}
	mutex_unlock(&fman->goal_irq_mutex);

}