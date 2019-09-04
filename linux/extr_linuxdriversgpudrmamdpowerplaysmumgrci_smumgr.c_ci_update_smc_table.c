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
typedef  int uint32_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
#define  SMU_UVD_TABLE 129 
#define  SMU_VCE_TABLE 128 
 int /*<<< orphan*/  ci_update_uvd_smc_table (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  ci_update_vce_smc_table (struct pp_hwmgr*) ; 

__attribute__((used)) static int ci_update_smc_table(struct pp_hwmgr *hwmgr, uint32_t type)
{
	switch (type) {
	case SMU_UVD_TABLE:
		ci_update_uvd_smc_table(hwmgr);
		break;
	case SMU_VCE_TABLE:
		ci_update_vce_smc_table(hwmgr);
		break;
	default:
		break;
	}
	return 0;
}