#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmw_cmdbuf_man {int /*<<< orphan*/  space_mutex; TYPE_1__* dev_priv; int /*<<< orphan*/  alloc_queue; } ;
struct vmw_cmdbuf_alloc_info {int page_size; int done; struct drm_mm_node* node; } ;
struct drm_mm_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmdbuf_waiters; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int PAGE_ALIGN (size_t) ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  SVGA_IRQFLAG_COMMAND_BUFFER ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vmw_cmdbuf_try_alloc (struct vmw_cmdbuf_man*,struct vmw_cmdbuf_alloc_info*) ; 
 int /*<<< orphan*/  vmw_generic_waiter_add (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmw_generic_waiter_remove (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,scalar_t__) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int vmw_cmdbuf_alloc_space(struct vmw_cmdbuf_man *man,
				  struct drm_mm_node *node,
				  size_t size,
				  bool interruptible)
{
	struct vmw_cmdbuf_alloc_info info;

	info.page_size = PAGE_ALIGN(size) >> PAGE_SHIFT;
	info.node = node;
	info.done = false;

	/*
	 * To prevent starvation of large requests, only one allocating call
	 * at a time waiting for space.
	 */
	if (interruptible) {
		if (mutex_lock_interruptible(&man->space_mutex))
			return -ERESTARTSYS;
	} else {
		mutex_lock(&man->space_mutex);
	}

	/* Try to allocate space without waiting. */
	if (vmw_cmdbuf_try_alloc(man, &info))
		goto out_unlock;

	vmw_generic_waiter_add(man->dev_priv,
			       SVGA_IRQFLAG_COMMAND_BUFFER,
			       &man->dev_priv->cmdbuf_waiters);

	if (interruptible) {
		int ret;

		ret = wait_event_interruptible
			(man->alloc_queue, vmw_cmdbuf_try_alloc(man, &info));
		if (ret) {
			vmw_generic_waiter_remove
				(man->dev_priv, SVGA_IRQFLAG_COMMAND_BUFFER,
				 &man->dev_priv->cmdbuf_waiters);
			mutex_unlock(&man->space_mutex);
			return ret;
		}
	} else {
		wait_event(man->alloc_queue, vmw_cmdbuf_try_alloc(man, &info));
	}
	vmw_generic_waiter_remove(man->dev_priv,
				  SVGA_IRQFLAG_COMMAND_BUFFER,
				  &man->dev_priv->cmdbuf_waiters);

out_unlock:
	mutex_unlock(&man->space_mutex);

	return 0;
}