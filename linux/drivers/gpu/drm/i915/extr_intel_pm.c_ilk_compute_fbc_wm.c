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
struct TYPE_6__ {int /*<<< orphan*/  dst; TYPE_2__* fb; } ;
struct intel_plane_state {TYPE_3__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct TYPE_5__ {TYPE_1__* format; } ;
struct TYPE_4__ {int* cpp; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_rect_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ilk_wm_fbc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intel_wm_plane_visible (struct intel_crtc_state const*,struct intel_plane_state const*) ; 

__attribute__((used)) static u32 ilk_compute_fbc_wm(const struct intel_crtc_state *crtc_state,
			      const struct intel_plane_state *plane_state,
			      u32 pri_val)
{
	int cpp;

	if (!intel_wm_plane_visible(crtc_state, plane_state))
		return 0;

	cpp = plane_state->base.fb->format->cpp[0];

	return ilk_wm_fbc(pri_val, drm_rect_width(&plane_state->base.dst), cpp);
}