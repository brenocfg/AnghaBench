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
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_2__ {struct drm_crtc crtc; } ;
struct xen_drm_front_drm_pipeline {int /*<<< orphan*/ * pending_event; TYPE_1__ pipe; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void send_pending_event(struct xen_drm_front_drm_pipeline *pipeline)
{
	struct drm_crtc *crtc = &pipeline->pipe.crtc;
	struct drm_device *dev = crtc->dev;
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	if (pipeline->pending_event)
		drm_crtc_send_vblank_event(crtc, pipeline->pending_event);
	pipeline->pending_event = NULL;
	spin_unlock_irqrestore(&dev->event_lock, flags);
}