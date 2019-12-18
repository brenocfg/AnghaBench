#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dclk; int /*<<< orphan*/  vclk; } ;
struct vega10_power_state {int dc_compatible; TYPE_2__ uvd_clks; } ;
struct TYPE_7__ {int /*<<< orphan*/  DCLK; int /*<<< orphan*/  VCLK; } ;
struct TYPE_5__ {int /*<<< orphan*/  disallowOnDC; } ;
struct TYPE_8__ {int /*<<< orphan*/  magic; } ;
struct pp_power_state {TYPE_3__ uvd_clocks; TYPE_1__ validation; TYPE_4__ hardware; } ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PhwVega10_Magic ; 
 struct vega10_power_state* cast_phw_vega10_power_state (TYPE_4__*) ; 
 int vega10_get_powerplay_table_entry (struct pp_hwmgr*,unsigned long,struct pp_power_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vega10_get_pp_table_entry_callback_func ; 

__attribute__((used)) static int vega10_get_pp_table_entry(struct pp_hwmgr *hwmgr,
		unsigned long entry_index, struct pp_power_state *state)
{
	int result;
	struct vega10_power_state *ps;

	state->hardware.magic = PhwVega10_Magic;

	ps = cast_phw_vega10_power_state(&state->hardware);

	result = vega10_get_powerplay_table_entry(hwmgr, entry_index, state,
			vega10_get_pp_table_entry_callback_func);

	/*
	 * This is the earliest time we have all the dependency table
	 * and the VBIOS boot state
	 */
	/* set DC compatible flag if this state supports DC */
	if (!state->validation.disallowOnDC)
		ps->dc_compatible = true;

	ps->uvd_clks.vclk = state->uvd_clocks.VCLK;
	ps->uvd_clks.dclk = state->uvd_clocks.DCLK;

	return 0;
}