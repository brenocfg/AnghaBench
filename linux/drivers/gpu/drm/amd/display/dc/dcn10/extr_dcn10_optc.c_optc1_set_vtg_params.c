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
typedef  int uint32_t ;
struct timing_generator {int dummy; } ;
struct optc {int vstartup_start; } ;
struct TYPE_2__ {int INTERLACE; } ;
struct dc_crtc_timing {int v_total; int v_front_porch; int v_border_bottom; int v_addressable; int v_border_top; TYPE_1__ flags; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL ; 
 struct optc* DCN10TG_FROM_TG (struct timing_generator*) ; 
 int /*<<< orphan*/  OTG_INTERLACE_CONTROL ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VTG0_FP2 ; 
 int /*<<< orphan*/  VTG0_VCOUNT_INIT ; 
 int /*<<< orphan*/  apply_front_porch_workaround (struct dc_crtc_timing*) ; 

void optc1_set_vtg_params(struct timing_generator *optc,
		const struct dc_crtc_timing *dc_crtc_timing)
{
	struct dc_crtc_timing patched_crtc_timing;
	uint32_t asic_blank_end;
	uint32_t v_init;
	uint32_t v_fp2 = 0;
	int32_t vertical_line_start;

	struct optc *optc1 = DCN10TG_FROM_TG(optc);

	patched_crtc_timing = *dc_crtc_timing;
	apply_front_porch_workaround(&patched_crtc_timing);

	/* VCOUNT_INIT is the start of blank */
	v_init = patched_crtc_timing.v_total - patched_crtc_timing.v_front_porch;

	/* end of blank = v_init - active */
	asic_blank_end = v_init -
			patched_crtc_timing.v_border_bottom -
			patched_crtc_timing.v_addressable -
			patched_crtc_timing.v_border_top;

	/* if VSTARTUP is before VSYNC, FP2 is the offset, otherwise 0 */
	vertical_line_start = asic_blank_end - optc1->vstartup_start + 1;
	if (vertical_line_start < 0)
		v_fp2 = -vertical_line_start;

	/* Interlace */
	if (REG(OTG_INTERLACE_CONTROL)) {
		if (patched_crtc_timing.flags.INTERLACE == 1) {
			v_init = v_init / 2;
			if ((optc1->vstartup_start/2)*2 > asic_blank_end)
				v_fp2 = v_fp2 / 2;
		}
	}

	REG_UPDATE_2(CONTROL,
			VTG0_FP2, v_fp2,
			VTG0_VCOUNT_INIT, v_init);
}