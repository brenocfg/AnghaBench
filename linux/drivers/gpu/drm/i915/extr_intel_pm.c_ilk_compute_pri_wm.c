#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_9__ {int /*<<< orphan*/  dst; TYPE_1__* fb; } ;
struct intel_plane_state {TYPE_4__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  crtc_htotal; } ;
struct TYPE_8__ {TYPE_2__ adjusted_mode; } ;
struct intel_crtc_state {TYPE_3__ base; int /*<<< orphan*/  pixel_rate; } ;
struct TYPE_10__ {int* cpp; } ;
struct TYPE_6__ {TYPE_5__* format; } ;

/* Variables and functions */
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  drm_rect_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ilk_wm_method1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilk_wm_method2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_wm_plane_visible (struct intel_crtc_state const*,struct intel_plane_state const*) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 ilk_compute_pri_wm(const struct intel_crtc_state *crtc_state,
			      const struct intel_plane_state *plane_state,
			      u32 mem_value, bool is_lp)
{
	u32 method1, method2;
	int cpp;

	if (mem_value == 0)
		return U32_MAX;

	if (!intel_wm_plane_visible(crtc_state, plane_state))
		return 0;

	cpp = plane_state->base.fb->format->cpp[0];

	method1 = ilk_wm_method1(crtc_state->pixel_rate, cpp, mem_value);

	if (!is_lp)
		return method1;

	method2 = ilk_wm_method2(crtc_state->pixel_rate,
				 crtc_state->base.adjusted_mode.crtc_htotal,
				 drm_rect_width(&plane_state->base.dst),
				 cpp, mem_value);

	return min(method1, method2);
}