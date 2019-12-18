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
struct drm_pending_event {TYPE_1__* file_priv; int /*<<< orphan*/  link; int /*<<< orphan*/  pending_link; scalar_t__ fence; int /*<<< orphan*/ * completion; int /*<<< orphan*/  (* completion_release ) (int /*<<< orphan*/ *) ;} ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_wait; int /*<<< orphan*/  event_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (scalar_t__) ; 
 int /*<<< orphan*/  dma_fence_signal (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct drm_pending_event*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void drm_send_event_locked(struct drm_device *dev, struct drm_pending_event *e)
{
	assert_spin_locked(&dev->event_lock);

	if (e->completion) {
		complete_all(e->completion);
		e->completion_release(e->completion);
		e->completion = NULL;
	}

	if (e->fence) {
		dma_fence_signal(e->fence);
		dma_fence_put(e->fence);
	}

	if (!e->file_priv) {
		kfree(e);
		return;
	}

	list_del(&e->pending_link);
	list_add_tail(&e->link,
		      &e->file_priv->event_list);
	wake_up_interruptible(&e->file_priv->event_wait);
}