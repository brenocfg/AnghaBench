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
typedef  scalar_t__ u32 ;
struct intf_timing_params {scalar_t__ v_back_porch; scalar_t__ vsync_pulse_width; scalar_t__ v_front_porch; } ;
struct dpu_encoder_phys {TYPE_2__* hw_intf; } ;
struct TYPE_4__ {TYPE_1__* cap; } ;
struct TYPE_3__ {scalar_t__ prog_fetch_lines_worst_case; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_DEBUG_VIDENC (struct dpu_encoder_phys*,char*,...) ; 
 int /*<<< orphan*/  pr_warn_once (char*) ; 

__attribute__((used)) static u32 programmable_fetch_get_num_lines(
		struct dpu_encoder_phys *phys_enc,
		const struct intf_timing_params *timing)
{
	u32 worst_case_needed_lines =
	    phys_enc->hw_intf->cap->prog_fetch_lines_worst_case;
	u32 start_of_frame_lines =
	    timing->v_back_porch + timing->vsync_pulse_width;
	u32 needed_vfp_lines = worst_case_needed_lines - start_of_frame_lines;
	u32 actual_vfp_lines = 0;

	/* Fetch must be outside active lines, otherwise undefined. */
	if (start_of_frame_lines >= worst_case_needed_lines) {
		DPU_DEBUG_VIDENC(phys_enc,
				"prog fetch is not needed, large vbp+vsw\n");
		actual_vfp_lines = 0;
	} else if (timing->v_front_porch < needed_vfp_lines) {
		/* Warn fetch needed, but not enough porch in panel config */
		pr_warn_once
			("low vbp+vfp may lead to perf issues in some cases\n");
		DPU_DEBUG_VIDENC(phys_enc,
				"less vfp than fetch req, using entire vfp\n");
		actual_vfp_lines = timing->v_front_porch;
	} else {
		DPU_DEBUG_VIDENC(phys_enc, "room in vfp for needed prefetch\n");
		actual_vfp_lines = needed_vfp_lines;
	}

	DPU_DEBUG_VIDENC(phys_enc,
		"v_front_porch %u v_back_porch %u vsync_pulse_width %u\n",
		timing->v_front_porch, timing->v_back_porch,
		timing->vsync_pulse_width);
	DPU_DEBUG_VIDENC(phys_enc,
		"wc_lines %u needed_vfp_lines %u actual_vfp_lines %u\n",
		worst_case_needed_lines, needed_vfp_lines, actual_vfp_lines);

	return actual_vfp_lines;
}