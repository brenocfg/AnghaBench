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
struct TYPE_4__ {struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_3__* color_plane; TYPE_1__ base; } ;
struct drm_framebuffer {TYPE_2__* format; } ;
struct TYPE_6__ {unsigned int stride; } ;
struct TYPE_5__ {unsigned int* cpp; } ;

/* Variables and functions */

u32 intel_fb_xy_to_linear(int x, int y,
			  const struct intel_plane_state *state,
			  int color_plane)
{
	const struct drm_framebuffer *fb = state->base.fb;
	unsigned int cpp = fb->format->cpp[color_plane];
	unsigned int pitch = state->color_plane[color_plane].stride;

	return y * pitch + x * cpp;
}