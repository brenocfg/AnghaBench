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
struct drm_simple_display_pipe {int dummy; } ;
struct drm_plane_state {TYPE_1__* fb; } ;
struct drm_gem_vram_object {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 struct drm_gem_vram_object* drm_gem_vram_of_gem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_vram_unpin (struct drm_gem_vram_object*) ; 

__attribute__((used)) static void bochs_pipe_cleanup_fb(struct drm_simple_display_pipe *pipe,
				  struct drm_plane_state *old_state)
{
	struct drm_gem_vram_object *gbo;

	if (!old_state->fb)
		return;
	gbo = drm_gem_vram_of_gem(old_state->fb->obj[0]);
	drm_gem_vram_unpin(gbo);
}