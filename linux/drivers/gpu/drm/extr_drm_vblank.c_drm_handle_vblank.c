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
struct drm_vblank_crtc {int /*<<< orphan*/  disable_timer; int /*<<< orphan*/  refcount; int /*<<< orphan*/  queue; int /*<<< orphan*/  enabled; } ;
struct drm_device {unsigned int num_crtcs; int /*<<< orphan*/  event_lock; scalar_t__ vblank_disable_immediate; int /*<<< orphan*/  vblank_time_lock; struct drm_vblank_crtc* vblank; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_handle_vblank_events (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  drm_update_vblank_count (struct drm_device*,unsigned int,int) ; 
 scalar_t__ drm_vblank_offdelay ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vblank_disable_fn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

bool drm_handle_vblank(struct drm_device *dev, unsigned int pipe)
{
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	unsigned long irqflags;
	bool disable_irq;

	if (WARN_ON_ONCE(!dev->num_crtcs))
		return false;

	if (WARN_ON(pipe >= dev->num_crtcs))
		return false;

	spin_lock_irqsave(&dev->event_lock, irqflags);

	/* Need timestamp lock to prevent concurrent execution with
	 * vblank enable/disable, as this would cause inconsistent
	 * or corrupted timestamps and vblank counts.
	 */
	spin_lock(&dev->vblank_time_lock);

	/* Vblank irq handling disabled. Nothing to do. */
	if (!vblank->enabled) {
		spin_unlock(&dev->vblank_time_lock);
		spin_unlock_irqrestore(&dev->event_lock, irqflags);
		return false;
	}

	drm_update_vblank_count(dev, pipe, true);

	spin_unlock(&dev->vblank_time_lock);

	wake_up(&vblank->queue);

	/* With instant-off, we defer disabling the interrupt until after
	 * we finish processing the following vblank after all events have
	 * been signaled. The disable has to be last (after
	 * drm_handle_vblank_events) so that the timestamp is always accurate.
	 */
	disable_irq = (dev->vblank_disable_immediate &&
		       drm_vblank_offdelay > 0 &&
		       !atomic_read(&vblank->refcount));

	drm_handle_vblank_events(dev, pipe);

	spin_unlock_irqrestore(&dev->event_lock, irqflags);

	if (disable_irq)
		vblank_disable_fn(&vblank->disable_timer);

	return true;
}