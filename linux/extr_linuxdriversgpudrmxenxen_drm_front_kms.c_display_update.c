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
struct xen_drm_front_drm_pipeline {struct drm_pending_vblank_event* pending_event; } ;
struct drm_crtc {struct drm_device* dev; TYPE_1__* state; } ;
struct drm_simple_display_pipe {struct drm_crtc crtc; } ;
struct drm_plane_state {int dummy; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct TYPE_2__ {struct drm_pending_vblank_event* event; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  display_send_page_flip (struct drm_simple_display_pipe*,struct drm_plane_state*) ; 
 int /*<<< orphan*/  drm_dev_enter (struct drm_device*,int*) ; 
 int /*<<< orphan*/  drm_dev_exit (int) ; 
 int /*<<< orphan*/  send_pending_event (struct xen_drm_front_drm_pipeline*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct xen_drm_front_drm_pipeline* to_xen_drm_pipeline (struct drm_simple_display_pipe*) ; 

__attribute__((used)) static void display_update(struct drm_simple_display_pipe *pipe,
			   struct drm_plane_state *old_plane_state)
{
	struct xen_drm_front_drm_pipeline *pipeline =
			to_xen_drm_pipeline(pipe);
	struct drm_crtc *crtc = &pipe->crtc;
	struct drm_pending_vblank_event *event;
	int idx;

	event = crtc->state->event;
	if (event) {
		struct drm_device *dev = crtc->dev;
		unsigned long flags;

		WARN_ON(pipeline->pending_event);

		spin_lock_irqsave(&dev->event_lock, flags);
		crtc->state->event = NULL;

		pipeline->pending_event = event;
		spin_unlock_irqrestore(&dev->event_lock, flags);
	}

	if (!drm_dev_enter(pipe->crtc.dev, &idx)) {
		send_pending_event(pipeline);
		return;
	}

	/*
	 * Send page flip request to the backend *after* we have event cached
	 * above, so on page flip done event from the backend we can
	 * deliver it and there is no race condition between this code and
	 * event from the backend.
	 * If this is not a page flip, e.g. no flip done event from the backend
	 * is expected, then send now.
	 */
	if (!display_send_page_flip(pipe, old_plane_state))
		send_pending_event(pipeline);

	drm_dev_exit(idx);
}