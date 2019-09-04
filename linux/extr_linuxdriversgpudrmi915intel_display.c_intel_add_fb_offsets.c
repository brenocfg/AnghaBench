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
struct TYPE_6__ {unsigned int rotation; int /*<<< orphan*/  fb; } ;
struct intel_plane_state {TYPE_3__ base; } ;
struct intel_framebuffer {TYPE_2__* normal; TYPE_1__* rotated; } ;
struct TYPE_5__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_4__ {scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 scalar_t__ drm_rotation_90_or_270 (unsigned int) ; 
 struct intel_framebuffer* to_intel_framebuffer (int /*<<< orphan*/ ) ; 

void intel_add_fb_offsets(int *x, int *y,
			  const struct intel_plane_state *state,
			  int plane)

{
	const struct intel_framebuffer *intel_fb = to_intel_framebuffer(state->base.fb);
	unsigned int rotation = state->base.rotation;

	if (drm_rotation_90_or_270(rotation)) {
		*x += intel_fb->rotated[plane].x;
		*y += intel_fb->rotated[plane].y;
	} else {
		*x += intel_fb->normal[plane].x;
		*y += intel_fb->normal[plane].y;
	}
}