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
struct drm_plane_state {int /*<<< orphan*/  fb; } ;
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int omap_framebuffer_pin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int omap_plane_prepare_fb(struct drm_plane *plane,
				 struct drm_plane_state *new_state)
{
	if (!new_state->fb)
		return 0;

	return omap_framebuffer_pin(new_state->fb);
}