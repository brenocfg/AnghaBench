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
struct drm_simple_display_pipe {int /*<<< orphan*/  plane; } ;
struct drm_plane_state {int dummy; } ;

/* Variables and functions */
 int drm_gem_fb_prepare_fb (int /*<<< orphan*/ *,struct drm_plane_state*) ; 

int drm_gem_fb_simple_display_pipe_prepare_fb(struct drm_simple_display_pipe *pipe,
					      struct drm_plane_state *plane_state)
{
	return drm_gem_fb_prepare_fb(&pipe->plane, plane_state);
}