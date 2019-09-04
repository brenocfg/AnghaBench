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
struct TYPE_4__ {int sr_exit_time_ns; int sr_enter_plus_exit_time_ns; int urgent_latency_ns; int percent_of_ideal_drambw; int dram_clock_change_latency_ns; } ;
struct dc {TYPE_2__ debug; TYPE_1__* dcn_soc; } ;
struct TYPE_3__ {int sr_exit_time; int sr_enter_plus_exit_time; int urgent_latency; int percent_of_ideal_drambw_received_after_urg_latency; int dram_clock_change_latency; } ;

/* Variables and functions */
 int /*<<< orphan*/  kernel_fpu_begin () ; 
 int /*<<< orphan*/  kernel_fpu_end () ; 

__attribute__((used)) static bool dcn_bw_apply_registry_override(struct dc *dc)
{
	bool updated = false;

	kernel_fpu_begin();
	if ((int)(dc->dcn_soc->sr_exit_time * 1000) != dc->debug.sr_exit_time_ns
			&& dc->debug.sr_exit_time_ns) {
		updated = true;
		dc->dcn_soc->sr_exit_time = dc->debug.sr_exit_time_ns / 1000.0;
	}

	if ((int)(dc->dcn_soc->sr_enter_plus_exit_time * 1000)
				!= dc->debug.sr_enter_plus_exit_time_ns
			&& dc->debug.sr_enter_plus_exit_time_ns) {
		updated = true;
		dc->dcn_soc->sr_enter_plus_exit_time =
				dc->debug.sr_enter_plus_exit_time_ns / 1000.0;
	}

	if ((int)(dc->dcn_soc->urgent_latency * 1000) != dc->debug.urgent_latency_ns
			&& dc->debug.urgent_latency_ns) {
		updated = true;
		dc->dcn_soc->urgent_latency = dc->debug.urgent_latency_ns / 1000.0;
	}

	if ((int)(dc->dcn_soc->percent_of_ideal_drambw_received_after_urg_latency * 1000)
				!= dc->debug.percent_of_ideal_drambw
			&& dc->debug.percent_of_ideal_drambw) {
		updated = true;
		dc->dcn_soc->percent_of_ideal_drambw_received_after_urg_latency =
				dc->debug.percent_of_ideal_drambw;
	}

	if ((int)(dc->dcn_soc->dram_clock_change_latency * 1000)
				!= dc->debug.dram_clock_change_latency_ns
			&& dc->debug.dram_clock_change_latency_ns) {
		updated = true;
		dc->dcn_soc->dram_clock_change_latency =
				dc->debug.dram_clock_change_latency_ns / 1000.0;
	}
	kernel_fpu_end();

	return updated;
}