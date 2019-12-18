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
struct amd_pp_clocks {int dummy; } ;
typedef  enum amd_pp_clock_type { ____Placeholder_amd_pp_clock_type } amd_pp_clock_type ;

/* Variables and functions */
 int EINVAL ; 
#define  amd_pp_mem_clock 129 
#define  amd_pp_sys_clock 128 
 int /*<<< orphan*/  smu7_get_mclks (struct pp_hwmgr*,struct amd_pp_clocks*) ; 
 int /*<<< orphan*/  smu7_get_sclks (struct pp_hwmgr*,struct amd_pp_clocks*) ; 

__attribute__((used)) static int smu7_get_clock_by_type(struct pp_hwmgr *hwmgr, enum amd_pp_clock_type type,
						struct amd_pp_clocks *clocks)
{
	switch (type) {
	case amd_pp_sys_clock:
		smu7_get_sclks(hwmgr, clocks);
		break;
	case amd_pp_mem_clock:
		smu7_get_mclks(hwmgr, clocks);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}