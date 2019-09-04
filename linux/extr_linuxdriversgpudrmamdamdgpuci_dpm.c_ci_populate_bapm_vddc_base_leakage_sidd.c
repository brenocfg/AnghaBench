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
typedef  int u16 ;
struct TYPE_8__ {int BapmVddCBaseLeakageHiSidd; int BapmVddCBaseLeakageLoSidd; } ;
struct ci_power_info {TYPE_4__ smc_powertune_table; } ;
struct TYPE_5__ {struct amdgpu_cac_tdp_table* cac_tdp_table; } ;
struct TYPE_6__ {TYPE_1__ dyn_state; } ;
struct TYPE_7__ {TYPE_2__ dpm; } ;
struct amdgpu_device {TYPE_3__ pm; } ;
struct amdgpu_cac_tdp_table {int high_cac_leakage; int low_cac_leakage; } ;

/* Variables and functions */
 struct ci_power_info* ci_get_pi (struct amdgpu_device*) ; 
 void* cpu_to_be16 (int) ; 

__attribute__((used)) static int ci_populate_bapm_vddc_base_leakage_sidd(struct amdgpu_device *adev)
{
	struct ci_power_info *pi = ci_get_pi(adev);
	u16 hi_sidd = pi->smc_powertune_table.BapmVddCBaseLeakageHiSidd;
	u16 lo_sidd = pi->smc_powertune_table.BapmVddCBaseLeakageLoSidd;
	struct amdgpu_cac_tdp_table *cac_tdp_table =
		adev->pm.dpm.dyn_state.cac_tdp_table;

	hi_sidd = cac_tdp_table->high_cac_leakage / 100 * 256;
	lo_sidd = cac_tdp_table->low_cac_leakage / 100 * 256;

	pi->smc_powertune_table.BapmVddCBaseLeakageHiSidd = cpu_to_be16(hi_sidd);
	pi->smc_powertune_table.BapmVddCBaseLeakageLoSidd = cpu_to_be16(lo_sidd);

	return 0;
}