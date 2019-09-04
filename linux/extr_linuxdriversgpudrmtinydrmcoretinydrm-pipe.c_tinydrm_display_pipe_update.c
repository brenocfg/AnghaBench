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
struct drm_crtc {TYPE_5__* state; TYPE_4__* dev; } ;
struct TYPE_8__ {struct drm_crtc crtc; } ;
struct tinydrm_device {int /*<<< orphan*/  (* fb_dirty ) (struct drm_framebuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;TYPE_3__ pipe; } ;
struct TYPE_7__ {TYPE_1__* state; } ;
struct drm_simple_display_pipe {TYPE_2__ plane; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_framebuffer {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/ * event; } ;
struct TYPE_9__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_6__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 struct tinydrm_device* pipe_to_tinydrm (struct drm_simple_display_pipe*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct drm_framebuffer*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void tinydrm_display_pipe_update(struct drm_simple_display_pipe *pipe,
				 struct drm_plane_state *old_state)
{
	struct tinydrm_device *tdev = pipe_to_tinydrm(pipe);
	struct drm_framebuffer *fb = pipe->plane.state->fb;
	struct drm_crtc *crtc = &tdev->pipe.crtc;

	if (fb && (fb != old_state->fb)) {
		if (tdev->fb_dirty)
			tdev->fb_dirty(fb, NULL, 0, 0, NULL, 0);
	}

	if (crtc->state->event) {
		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		spin_unlock_irq(&crtc->dev->event_lock);
		crtc->state->event = NULL;
	}
}