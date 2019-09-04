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
typedef  int uint32_t ;
struct TYPE_4__ {int vstartup_start; } ;
struct timing_generator {TYPE_2__ dlg_otg_param; } ;
struct TYPE_3__ {scalar_t__ INTERLACE; } ;
struct dc_crtc_timing {int h_addressable; int h_border_right; int h_front_porch; int h_total; int h_border_left; int v_addressable; int v_border_bottom; int v_front_porch; int v_total; int v_border_top; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optc1_apply_front_porch_workaround (struct timing_generator*,struct dc_crtc_timing*) ; 

__attribute__((used)) static uint32_t get_start_vline(struct timing_generator *optc, const struct dc_crtc_timing *dc_crtc_timing)
{
	struct dc_crtc_timing patched_crtc_timing;
	int vesa_sync_start;
	int asic_blank_end;
	int interlace_factor;
	int vertical_line_start;

	patched_crtc_timing = *dc_crtc_timing;
	optc1_apply_front_porch_workaround(optc, &patched_crtc_timing);

	vesa_sync_start = patched_crtc_timing.h_addressable +
			patched_crtc_timing.h_border_right +
			patched_crtc_timing.h_front_porch;

	asic_blank_end = patched_crtc_timing.h_total -
			vesa_sync_start -
			patched_crtc_timing.h_border_left;

	interlace_factor = patched_crtc_timing.flags.INTERLACE ? 2 : 1;

	vesa_sync_start = patched_crtc_timing.v_addressable +
			patched_crtc_timing.v_border_bottom +
			patched_crtc_timing.v_front_porch;

	asic_blank_end = (patched_crtc_timing.v_total -
			vesa_sync_start -
			patched_crtc_timing.v_border_top)
			* interlace_factor;

	vertical_line_start = asic_blank_end - optc->dlg_otg_param.vstartup_start + 1;
	if (vertical_line_start < 0) {
		ASSERT(0);
		vertical_line_start = 0;
	}

	return vertical_line_start;
}