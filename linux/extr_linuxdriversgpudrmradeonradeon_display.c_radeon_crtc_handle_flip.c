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
struct radeon_flip_work {int /*<<< orphan*/  unpin_work; int /*<<< orphan*/  crtc_id; scalar_t__ event; } ;
struct TYPE_3__ {struct radeon_crtc** crtcs; } ;
struct radeon_device {TYPE_2__* ddev; TYPE_1__ mode_info; } ;
struct radeon_crtc {scalar_t__ flip_status; int /*<<< orphan*/  flip_queue; int /*<<< orphan*/  base; struct radeon_flip_work* flip_work; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ RADEON_FLIP_NONE ; 
 scalar_t__ RADEON_FLIP_SUBMITTED ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_irq_kms_pflip_irq_put (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void radeon_crtc_handle_flip(struct radeon_device *rdev, int crtc_id)
{
	struct radeon_crtc *radeon_crtc = rdev->mode_info.crtcs[crtc_id];
	struct radeon_flip_work *work;
	unsigned long flags;

	/* this can happen at init */
	if (radeon_crtc == NULL)
		return;

	spin_lock_irqsave(&rdev->ddev->event_lock, flags);
	work = radeon_crtc->flip_work;
	if (radeon_crtc->flip_status != RADEON_FLIP_SUBMITTED) {
		DRM_DEBUG_DRIVER("radeon_crtc->flip_status = %d != "
				 "RADEON_FLIP_SUBMITTED(%d)\n",
				 radeon_crtc->flip_status,
				 RADEON_FLIP_SUBMITTED);
		spin_unlock_irqrestore(&rdev->ddev->event_lock, flags);
		return;
	}

	/* Pageflip completed. Clean up. */
	radeon_crtc->flip_status = RADEON_FLIP_NONE;
	radeon_crtc->flip_work = NULL;

	/* wakeup userspace */
	if (work->event)
		drm_crtc_send_vblank_event(&radeon_crtc->base, work->event);

	spin_unlock_irqrestore(&rdev->ddev->event_lock, flags);

	drm_crtc_vblank_put(&radeon_crtc->base);
	radeon_irq_kms_pflip_irq_put(rdev, work->crtc_id);
	queue_work(radeon_crtc->flip_queue, &work->unpin_work);
}