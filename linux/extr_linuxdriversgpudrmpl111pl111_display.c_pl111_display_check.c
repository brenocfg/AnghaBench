#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* state; } ;
struct drm_simple_display_pipe {TYPE_2__ plane; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_framebuffer {int* pitches; TYPE_3__* format; } ;
struct drm_display_mode {int hdisplay; } ;
struct drm_crtc_state {int mode_changed; struct drm_display_mode mode; } ;
struct TYPE_6__ {int* cpp; } ;
struct TYPE_4__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int EINVAL ; 
 int drm_fb_cma_get_gem_addr (struct drm_framebuffer*,struct drm_plane_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pl111_display_check(struct drm_simple_display_pipe *pipe,
			       struct drm_plane_state *pstate,
			       struct drm_crtc_state *cstate)
{
	const struct drm_display_mode *mode = &cstate->mode;
	struct drm_framebuffer *old_fb = pipe->plane.state->fb;
	struct drm_framebuffer *fb = pstate->fb;

	if (mode->hdisplay % 16)
		return -EINVAL;

	if (fb) {
		u32 offset = drm_fb_cma_get_gem_addr(fb, pstate, 0);

		/* FB base address must be dword aligned. */
		if (offset & 3)
			return -EINVAL;

		/* There's no pitch register -- the mode's hdisplay
		 * controls it.
		 */
		if (fb->pitches[0] != mode->hdisplay * fb->format->cpp[0])
			return -EINVAL;

		/* We can't change the FB format in a flicker-free
		 * manner (and only update it during CRTC enable).
		 */
		if (old_fb && old_fb->format != fb->format)
			cstate->mode_changed = true;
	}

	return 0;
}