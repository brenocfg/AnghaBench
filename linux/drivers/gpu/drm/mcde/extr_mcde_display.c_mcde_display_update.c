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
struct mcde {int /*<<< orphan*/  dev; } ;
struct drm_plane {struct drm_plane_state* state; } ;
struct drm_crtc {struct drm_device* dev; TYPE_1__* state; } ;
struct drm_simple_display_pipe {struct drm_plane plane; struct drm_crtc crtc; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_device {int /*<<< orphan*/  event_lock; struct mcde* dev_private; } ;
struct TYPE_2__ {scalar_t__ active; struct drm_pending_vblank_event* event; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info_once (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_crtc_arm_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 scalar_t__ drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_fb_cma_get_gem_addr (struct drm_framebuffer*,struct drm_plane_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcde_display_send_one_frame (struct mcde*) ; 
 int /*<<< orphan*/  mcde_set_extsrc (struct mcde*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mcde_display_update(struct drm_simple_display_pipe *pipe,
				struct drm_plane_state *old_pstate)
{
	struct drm_crtc *crtc = &pipe->crtc;
	struct drm_device *drm = crtc->dev;
	struct mcde *mcde = drm->dev_private;
	struct drm_pending_vblank_event *event = crtc->state->event;
	struct drm_plane *plane = &pipe->plane;
	struct drm_plane_state *pstate = plane->state;
	struct drm_framebuffer *fb = pstate->fb;

	/*
	 * Handle any pending event first, we need to arm the vblank
	 * interrupt before sending any update to the display so we don't
	 * miss the interrupt.
	 */
	if (event) {
		crtc->state->event = NULL;

		spin_lock_irq(&crtc->dev->event_lock);
		/*
		 * Hardware must be on before we can arm any vblank event,
		 * this is not a scanout controller where there is always
		 * some periodic update going on, it is completely frozen
		 * until we get an update. If MCDE output isn't yet enabled,
		 * we just send a vblank dummy event back.
		 */
		if (crtc->state->active && drm_crtc_vblank_get(crtc) == 0) {
			dev_dbg(mcde->dev, "arm vblank event\n");
			drm_crtc_arm_vblank_event(crtc, event);
		} else {
			dev_dbg(mcde->dev, "insert fake vblank event\n");
			drm_crtc_send_vblank_event(crtc, event);
		}

		spin_unlock_irq(&crtc->dev->event_lock);
	}

	/*
	 * We do not start sending framebuffer updates before the
	 * display is enabled. Update events will however be dispatched
	 * from the DRM core before the display is enabled.
	 */
	if (fb) {
		mcde_set_extsrc(mcde, drm_fb_cma_get_gem_addr(fb, pstate, 0));
		/* Send a single frame using software sync */
		mcde_display_send_one_frame(mcde);
		dev_info_once(mcde->dev, "sent first display update\n");
	} else {
		/*
		 * If an update is receieved before the MCDE is enabled
		 * (before mcde_display_enable() is called) we can't really
		 * do much with that buffer.
		 */
		dev_info(mcde->dev, "ignored a display update\n");
	}
}