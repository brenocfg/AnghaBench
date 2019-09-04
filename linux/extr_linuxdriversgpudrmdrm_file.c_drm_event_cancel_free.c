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
struct drm_pending_event {scalar_t__ fence; int /*<<< orphan*/  pending_link; TYPE_2__* event; TYPE_1__* file_priv; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct TYPE_4__ {scalar_t__ length; } ;
struct TYPE_3__ {int /*<<< orphan*/  event_space; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_fence_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct drm_pending_event*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void drm_event_cancel_free(struct drm_device *dev,
			   struct drm_pending_event *p)
{
	unsigned long flags;
	spin_lock_irqsave(&dev->event_lock, flags);
	if (p->file_priv) {
		p->file_priv->event_space += p->event->length;
		list_del(&p->pending_link);
	}
	spin_unlock_irqrestore(&dev->event_lock, flags);

	if (p->fence)
		dma_fence_put(p->fence);

	kfree(p);
}