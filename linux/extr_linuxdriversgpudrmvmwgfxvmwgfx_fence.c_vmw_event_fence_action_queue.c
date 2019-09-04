#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vmw_fence_obj {int dummy; } ;
struct vmw_fence_manager {TYPE_1__* dev_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  seq_passed; } ;
struct vmw_event_fence_action {TYPE_2__ action; int /*<<< orphan*/ * tv_usec; int /*<<< orphan*/ * tv_sec; int /*<<< orphan*/  dev; int /*<<< orphan*/  fence; struct drm_pending_event* event; } ;
struct drm_pending_event {int dummy; } ;
struct drm_file {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VMW_ACTION_EVENT ; 
 struct vmw_fence_manager* fman_from_fence (struct vmw_fence_obj*) ; 
 struct vmw_event_fence_action* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vmw_event_fence_action_cleanup ; 
 int /*<<< orphan*/  vmw_event_fence_action_seq_passed ; 
 int /*<<< orphan*/  vmw_fence_obj_add_action (struct vmw_fence_obj*,TYPE_2__*) ; 
 int /*<<< orphan*/  vmw_fence_obj_reference (struct vmw_fence_obj*) ; 

int vmw_event_fence_action_queue(struct drm_file *file_priv,
				 struct vmw_fence_obj *fence,
				 struct drm_pending_event *event,
				 uint32_t *tv_sec,
				 uint32_t *tv_usec,
				 bool interruptible)
{
	struct vmw_event_fence_action *eaction;
	struct vmw_fence_manager *fman = fman_from_fence(fence);

	eaction = kzalloc(sizeof(*eaction), GFP_KERNEL);
	if (unlikely(!eaction))
		return -ENOMEM;

	eaction->event = event;

	eaction->action.seq_passed = vmw_event_fence_action_seq_passed;
	eaction->action.cleanup = vmw_event_fence_action_cleanup;
	eaction->action.type = VMW_ACTION_EVENT;

	eaction->fence = vmw_fence_obj_reference(fence);
	eaction->dev = fman->dev_priv->dev;
	eaction->tv_sec = tv_sec;
	eaction->tv_usec = tv_usec;

	vmw_fence_obj_add_action(fence, &eaction->action);

	return 0;
}