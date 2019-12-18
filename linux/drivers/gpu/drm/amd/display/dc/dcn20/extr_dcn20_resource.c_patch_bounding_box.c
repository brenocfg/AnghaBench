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
struct TYPE_2__ {int sr_exit_time_ns; int sr_enter_plus_exit_time_ns; int urgent_latency_ns; int dram_clock_change_latency_ns; } ;
struct dc {TYPE_1__ bb_overrides; } ;
struct _vcs_dpi_soc_bounding_box_st {int sr_exit_time_us; int sr_enter_plus_exit_time_us; int urgent_latency_us; int dram_clock_change_latency_us; } ;

/* Variables and functions */
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 

__attribute__((used)) static void patch_bounding_box(struct dc *dc, struct _vcs_dpi_soc_bounding_box_st *bb)
{
	kernel_fpu_begin();
	if ((int)(bb->sr_exit_time_us * 1000) != dc->bb_overrides.sr_exit_time_ns
			&& dc->bb_overrides.sr_exit_time_ns) {
		bb->sr_exit_time_us = dc->bb_overrides.sr_exit_time_ns / 1000.0;
	}

	if ((int)(bb->sr_enter_plus_exit_time_us * 1000)
				!= dc->bb_overrides.sr_enter_plus_exit_time_ns
			&& dc->bb_overrides.sr_enter_plus_exit_time_ns) {
		bb->sr_enter_plus_exit_time_us =
				dc->bb_overrides.sr_enter_plus_exit_time_ns / 1000.0;
	}

	if ((int)(bb->urgent_latency_us * 1000) != dc->bb_overrides.urgent_latency_ns
			&& dc->bb_overrides.urgent_latency_ns) {
		bb->urgent_latency_us = dc->bb_overrides.urgent_latency_ns / 1000.0;
	}

	if ((int)(bb->dram_clock_change_latency_us * 1000)
				!= dc->bb_overrides.dram_clock_change_latency_ns
			&& dc->bb_overrides.dram_clock_change_latency_ns) {
		bb->dram_clock_change_latency_us =
				dc->bb_overrides.dram_clock_change_latency_ns / 1000.0;
	}
	kernel_fpu_end();
}