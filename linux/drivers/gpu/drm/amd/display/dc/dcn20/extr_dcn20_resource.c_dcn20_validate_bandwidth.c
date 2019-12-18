#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct display_mode_lib {int dummy; } ;
struct TYPE_10__ {double dram_clock_change_latency_us; double dummy_pstate_latency_us; } ;
struct TYPE_12__ {TYPE_4__ soc; } ;
struct TYPE_7__ {int p_state_change_support; } ;
struct TYPE_8__ {TYPE_1__ clk; } ;
struct TYPE_9__ {TYPE_2__ dcn; } ;
struct TYPE_11__ {TYPE_6__ dml; TYPE_3__ bw; } ;
struct dc_state {TYPE_5__ bw_ctx; } ;
struct dc {int /*<<< orphan*/  dml; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int dcn20_validate_bandwidth_internal (struct dc*,struct dc_state*,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,int /*<<< orphan*/ *,int) ; 

bool dcn20_validate_bandwidth(struct dc *dc, struct dc_state *context,
		bool fast_validate)
{
	bool voltage_supported = false;
	bool full_pstate_supported = false;
	bool dummy_pstate_supported = false;
	double p_state_latency_us = context->bw_ctx.dml.soc.dram_clock_change_latency_us;

	if (fast_validate)
		return dcn20_validate_bandwidth_internal(dc, context, true);


	// Best case, we support full UCLK switch latency
	voltage_supported = dcn20_validate_bandwidth_internal(dc, context, false);
	full_pstate_supported = context->bw_ctx.bw.dcn.clk.p_state_change_support;

	if (context->bw_ctx.dml.soc.dummy_pstate_latency_us == 0 ||
		(voltage_supported && full_pstate_supported)) {
		context->bw_ctx.bw.dcn.clk.p_state_change_support = true;
		goto restore_dml_state;
	}

	// Fallback: Try to only support G6 temperature read latency
	context->bw_ctx.dml.soc.dram_clock_change_latency_us = context->bw_ctx.dml.soc.dummy_pstate_latency_us;

	voltage_supported = dcn20_validate_bandwidth_internal(dc, context, false);
	dummy_pstate_supported = context->bw_ctx.bw.dcn.clk.p_state_change_support;

	if (voltage_supported && dummy_pstate_supported) {
		context->bw_ctx.bw.dcn.clk.p_state_change_support = false;
		goto restore_dml_state;
	}

	// ERROR: fallback is supposed to always work.
	ASSERT(false);

restore_dml_state:
	memcpy(&context->bw_ctx.dml, &dc->dml, sizeof(struct display_mode_lib));
	context->bw_ctx.dml.soc.dram_clock_change_latency_us = p_state_latency_us;

	return voltage_supported;
}