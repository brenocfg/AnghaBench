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
struct drm_simple_display_pipe {int dummy; } ;
struct drm_plane_state {struct drm_framebuffer* fb; } ;
struct drm_framebuffer {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_crtc_state {int dummy; } ;

/* Variables and functions */
 int cirrus_check_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_framebuffer*) ; 

__attribute__((used)) static int cirrus_pipe_check(struct drm_simple_display_pipe *pipe,
			     struct drm_plane_state *plane_state,
			     struct drm_crtc_state *crtc_state)
{
	struct drm_framebuffer *fb = plane_state->fb;

	if (!fb)
		return 0;
	return cirrus_check_size(fb->width, fb->height, fb);
}