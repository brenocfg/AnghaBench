#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pp_hwmgr {int dummy; } ;
struct pp_clock_levels_with_latency {int dummy; } ;
typedef  enum amd_pp_clock_type { ____Placeholder_amd_pp_clock_type } amd_pp_clock_type ;

/* Variables and functions */
#define  amd_pp_dcef_clock 131 
#define  amd_pp_mem_clock 130 
#define  amd_pp_soc_clock 129 
#define  amd_pp_sys_clock 128 
 int /*<<< orphan*/  vega10_get_dcefclocks (struct pp_hwmgr*,struct pp_clock_levels_with_latency*) ; 
 int /*<<< orphan*/  vega10_get_memclocks (struct pp_hwmgr*,struct pp_clock_levels_with_latency*) ; 
 int /*<<< orphan*/  vega10_get_sclks (struct pp_hwmgr*,struct pp_clock_levels_with_latency*) ; 
 int /*<<< orphan*/  vega10_get_socclocks (struct pp_hwmgr*,struct pp_clock_levels_with_latency*) ; 

__attribute__((used)) static int vega10_get_clock_by_type_with_latency(struct pp_hwmgr *hwmgr,
		enum amd_pp_clock_type type,
		struct pp_clock_levels_with_latency *clocks)
{
	switch (type) {
	case amd_pp_sys_clock:
		vega10_get_sclks(hwmgr, clocks);
		break;
	case amd_pp_mem_clock:
		vega10_get_memclocks(hwmgr, clocks);
		break;
	case amd_pp_dcef_clock:
		vega10_get_dcefclocks(hwmgr, clocks);
		break;
	case amd_pp_soc_clock:
		vega10_get_socclocks(hwmgr, clocks);
		break;
	default:
		return -1;
	}

	return 0;
}