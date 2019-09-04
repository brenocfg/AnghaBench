#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* state; } ;
struct drm_crtc {TYPE_4__* dev; TYPE_3__* state; } ;
struct drm_simple_display_pipe {TYPE_2__ plane; struct drm_crtc crtc; } ;
struct mxsfb_drm_private {TYPE_5__* devdata; scalar_t__ base; struct drm_simple_display_pipe pipe; } ;
struct drm_plane_state {int dummy; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_gem_cma_object {int /*<<< orphan*/  paddr; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_10__ {scalar_t__ next_buf; } ;
struct TYPE_9__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_8__ {struct drm_pending_vblank_event* event; } ;
struct TYPE_6__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_arm_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 scalar_t__ drm_crtc_vblank_get (struct drm_crtc*) ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxsfb_disable_axi_clk (struct mxsfb_drm_private*) ; 
 int /*<<< orphan*/  mxsfb_enable_axi_clk (struct mxsfb_drm_private*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void mxsfb_plane_atomic_update(struct mxsfb_drm_private *mxsfb,
			       struct drm_plane_state *state)
{
	struct drm_simple_display_pipe *pipe = &mxsfb->pipe;
	struct drm_crtc *crtc = &pipe->crtc;
	struct drm_framebuffer *fb = pipe->plane.state->fb;
	struct drm_pending_vblank_event *event;
	struct drm_gem_cma_object *gem;

	if (!crtc)
		return;

	spin_lock_irq(&crtc->dev->event_lock);
	event = crtc->state->event;
	if (event) {
		crtc->state->event = NULL;

		if (drm_crtc_vblank_get(crtc) == 0) {
			drm_crtc_arm_vblank_event(crtc, event);
		} else {
			drm_crtc_send_vblank_event(crtc, event);
		}
	}
	spin_unlock_irq(&crtc->dev->event_lock);

	if (!fb)
		return;

	gem = drm_fb_cma_get_gem_obj(fb, 0);

	mxsfb_enable_axi_clk(mxsfb);
	writel(gem->paddr, mxsfb->base + mxsfb->devdata->next_buf);
	mxsfb_disable_axi_clk(mxsfb);
}