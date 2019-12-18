#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct wm_range_table_entry {double pstate_latency_us; } ;
struct TYPE_17__ {double dram_clock_change_latency_us; int num_states; TYPE_2__* clock_limits; } ;
struct display_mode_lib {TYPE_4__ soc; } ;
struct TYPE_16__ {int cstate_enter_plus_exit_ns; int cstate_exit_ns; int pstate_change_ns; } ;
struct dcn_watermarks {int urgent_ns; int pte_meta_urgent_ns; int frac_urg_bw_nom; int frac_urg_bw_flip; TYPE_3__ cstate_pstate; } ;
struct TYPE_14__ {int voltage; int /*<<< orphan*/  socclk_mhz; int /*<<< orphan*/  dcfclk_mhz; } ;
struct TYPE_18__ {TYPE_1__ clks_cfg; } ;
typedef  TYPE_5__ display_e2e_pipe_params_st ;
struct TYPE_15__ {int /*<<< orphan*/  socclk_mhz; int /*<<< orphan*/  dcfclk_mhz; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int get_fraction_of_urgent_bandwidth (struct display_mode_lib*,TYPE_5__*,int) ; 
 int get_fraction_of_urgent_bandwidth_imm_flip (struct display_mode_lib*,TYPE_5__*,int) ; 
 int get_wm_dram_clock_change (struct display_mode_lib*,TYPE_5__*,int) ; 
 int get_wm_memory_trip (struct display_mode_lib*,TYPE_5__*,int) ; 
 int get_wm_stutter_enter_exit (struct display_mode_lib*,TYPE_5__*,int) ; 
 int get_wm_stutter_exit (struct display_mode_lib*,TYPE_5__*,int) ; 
 int get_wm_urgent (struct display_mode_lib*,TYPE_5__*,int) ; 

__attribute__((used)) static void calculate_wm_set_for_vlevel(
		int vlevel,
		struct wm_range_table_entry *table_entry,
		struct dcn_watermarks *wm_set,
		struct display_mode_lib *dml,
		display_e2e_pipe_params_st *pipes,
		int pipe_cnt)
{
	double dram_clock_change_latency_cached = dml->soc.dram_clock_change_latency_us;

	ASSERT(vlevel < dml->soc.num_states);
	/* only pipe 0 is read for voltage and dcf/soc clocks */
	pipes[0].clks_cfg.voltage = vlevel;
	pipes[0].clks_cfg.dcfclk_mhz = dml->soc.clock_limits[vlevel].dcfclk_mhz;
	pipes[0].clks_cfg.socclk_mhz = dml->soc.clock_limits[vlevel].socclk_mhz;

	dml->soc.dram_clock_change_latency_us = table_entry->pstate_latency_us;

	wm_set->urgent_ns = get_wm_urgent(dml, pipes, pipe_cnt) * 1000;
	wm_set->cstate_pstate.cstate_enter_plus_exit_ns = get_wm_stutter_enter_exit(dml, pipes, pipe_cnt) * 1000;
	wm_set->cstate_pstate.cstate_exit_ns = get_wm_stutter_exit(dml, pipes, pipe_cnt) * 1000;
	wm_set->cstate_pstate.pstate_change_ns = get_wm_dram_clock_change(dml, pipes, pipe_cnt) * 1000;
	wm_set->pte_meta_urgent_ns = get_wm_memory_trip(dml, pipes, pipe_cnt) * 1000;
#if defined(CONFIG_DRM_AMD_DC_DCN2_1)
	wm_set->frac_urg_bw_nom = get_fraction_of_urgent_bandwidth(dml, pipes, pipe_cnt) * 1000;
	wm_set->frac_urg_bw_flip = get_fraction_of_urgent_bandwidth_imm_flip(dml, pipes, pipe_cnt) * 1000;
#endif
	dml->soc.dram_clock_change_latency_us = dram_clock_change_latency_cached;

}