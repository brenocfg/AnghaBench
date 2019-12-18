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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int pixel_blend_mode; TYPE_2__* fb; } ;
struct intel_plane_state {TYPE_3__ base; } ;
struct TYPE_5__ {TYPE_1__* format; } ;
struct TYPE_4__ {int /*<<< orphan*/  has_alpha; } ;

/* Variables and functions */
#define  DRM_MODE_BLEND_COVERAGE 130 
#define  DRM_MODE_BLEND_PIXEL_NONE 129 
#define  DRM_MODE_BLEND_PREMULTI 128 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int /*<<< orphan*/  PLANE_COLOR_ALPHA_DISABLE ; 
 int /*<<< orphan*/  PLANE_COLOR_ALPHA_HW_PREMULTIPLY ; 
 int /*<<< orphan*/  PLANE_COLOR_ALPHA_SW_PREMULTIPLY ; 

__attribute__((used)) static u32 glk_plane_color_ctl_alpha(const struct intel_plane_state *plane_state)
{
	if (!plane_state->base.fb->format->has_alpha)
		return PLANE_COLOR_ALPHA_DISABLE;

	switch (plane_state->base.pixel_blend_mode) {
	case DRM_MODE_BLEND_PIXEL_NONE:
		return PLANE_COLOR_ALPHA_DISABLE;
	case DRM_MODE_BLEND_PREMULTI:
		return PLANE_COLOR_ALPHA_SW_PREMULTIPLY;
	case DRM_MODE_BLEND_COVERAGE:
		return PLANE_COLOR_ALPHA_HW_PREMULTIPLY;
	default:
		MISSING_CASE(plane_state->base.pixel_blend_mode);
		return PLANE_COLOR_ALPHA_DISABLE;
	}
}