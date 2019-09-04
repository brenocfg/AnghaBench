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

/* Variables and functions */
 int /*<<< orphan*/  SMU_UVD_TABLE ; 
 int smu7_enable_disable_uvd_dpm (struct pp_hwmgr*,int) ; 
 int /*<<< orphan*/  smum_update_smc_table (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu7_update_uvd_dpm(struct pp_hwmgr *hwmgr, bool bgate)
{
	if (!bgate)
		smum_update_smc_table(hwmgr, SMU_UVD_TABLE);
	return smu7_enable_disable_uvd_dpm(hwmgr, !bgate);
}