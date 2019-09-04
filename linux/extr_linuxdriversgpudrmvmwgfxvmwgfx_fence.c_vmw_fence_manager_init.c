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
struct vmw_user_fence {int dummy; } ;
struct vmw_private {int dummy; } ;
struct vmw_fence_obj {int dummy; } ;
struct vmw_fence_manager {int fifo_down; int /*<<< orphan*/  ctx; int /*<<< orphan*/  goal_irq_mutex; void* event_fence_action_size; void* fence_size; void* user_fence_size; int /*<<< orphan*/  work; int /*<<< orphan*/  cleanup_list; int /*<<< orphan*/  fence_list; int /*<<< orphan*/  lock; struct vmw_private* dev_priv; } ;
struct vmw_event_fence_action {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 struct vmw_fence_manager* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 void* ttm_round_pot (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_fence_work_func ; 

struct vmw_fence_manager *vmw_fence_manager_init(struct vmw_private *dev_priv)
{
	struct vmw_fence_manager *fman = kzalloc(sizeof(*fman), GFP_KERNEL);

	if (unlikely(!fman))
		return NULL;

	fman->dev_priv = dev_priv;
	spin_lock_init(&fman->lock);
	INIT_LIST_HEAD(&fman->fence_list);
	INIT_LIST_HEAD(&fman->cleanup_list);
	INIT_WORK(&fman->work, &vmw_fence_work_func);
	fman->fifo_down = true;
	fman->user_fence_size = ttm_round_pot(sizeof(struct vmw_user_fence));
	fman->fence_size = ttm_round_pot(sizeof(struct vmw_fence_obj));
	fman->event_fence_action_size =
		ttm_round_pot(sizeof(struct vmw_event_fence_action));
	mutex_init(&fman->goal_irq_mutex);
	fman->ctx = dma_fence_context_alloc(1);

	return fman;
}