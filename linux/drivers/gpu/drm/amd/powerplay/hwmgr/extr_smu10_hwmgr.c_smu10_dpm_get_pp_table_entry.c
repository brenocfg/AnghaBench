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
struct TYPE_4__ {int /*<<< orphan*/  dclk; int /*<<< orphan*/  vclk; } ;
struct smu10_power_state {TYPE_1__ uvd_clocks; } ;
struct TYPE_5__ {int /*<<< orphan*/  DCLK; int /*<<< orphan*/  VCLK; } ;
struct TYPE_6__ {int /*<<< orphan*/  magic; } ;
struct pp_power_state {TYPE_2__ uvd_clocks; TYPE_3__ hardware; } ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMU10_Magic ; 
 struct smu10_power_state* cast_smu10_ps (TYPE_3__*) ; 
 int pp_tables_get_entry (struct pp_hwmgr*,unsigned long,struct pp_power_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smu10_dpm_get_pp_table_entry_callback ; 

__attribute__((used)) static int smu10_dpm_get_pp_table_entry(struct pp_hwmgr *hwmgr,
		    unsigned long entry, struct pp_power_state *ps)
{
	int result;
	struct smu10_power_state *smu10_ps;

	ps->hardware.magic = SMU10_Magic;

	smu10_ps = cast_smu10_ps(&(ps->hardware));

	result = pp_tables_get_entry(hwmgr, entry, ps,
			smu10_dpm_get_pp_table_entry_callback);

	smu10_ps->uvd_clocks.vclk = ps->uvd_clocks.VCLK;
	smu10_ps->uvd_clocks.dclk = ps->uvd_clocks.DCLK;

	return result;
}