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
typedef  int u32 ;
struct TYPE_2__ {struct drm_framebuffer* fb; } ;
struct intel_plane_state {TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/ * pitches; } ;

/* Variables and functions */
 int CURSOR_ENABLE ; 
 int CURSOR_FORMAT_ARGB ; 
 int CURSOR_GAMMA_ENABLE ; 
 int CURSOR_STRIDE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 i845_cursor_ctl(const struct intel_crtc_state *crtc_state,
			   const struct intel_plane_state *plane_state)
{
	const struct drm_framebuffer *fb = plane_state->base.fb;

	return CURSOR_ENABLE |
		CURSOR_GAMMA_ENABLE |
		CURSOR_FORMAT_ARGB |
		CURSOR_STRIDE(fb->pitches[0]);
}