#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_plane_state {TYPE_2__* fb; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; } ;
struct TYPE_3__ {scalar_t__ offset; } ;
struct drm_gem_vram_object {TYPE_1__ bo; } ;
struct bochs_device {int /*<<< orphan*/  stride; } ;
struct TYPE_4__ {int /*<<< orphan*/  format; scalar_t__* offsets; int /*<<< orphan*/ * pitches; int /*<<< orphan*/ * obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  bochs_hw_setbase (struct bochs_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bochs_hw_setformat (struct bochs_device*,int /*<<< orphan*/ ) ; 
 struct drm_gem_vram_object* drm_gem_vram_of_gem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bochs_plane_update(struct bochs_device *bochs,
			       struct drm_plane_state *state)
{
	struct drm_gem_vram_object *gbo;

	if (!state->fb || !bochs->stride)
		return;

	gbo = drm_gem_vram_of_gem(state->fb->obj[0]);
	bochs_hw_setbase(bochs,
			 state->crtc_x,
			 state->crtc_y,
			 state->fb->pitches[0],
			 state->fb->offsets[0] + gbo->bo.offset);
	bochs_hw_setformat(bochs, state->fb->format);
}