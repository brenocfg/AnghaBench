#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint16_t ;
struct TYPE_2__ {void* BapmVddCBaseLeakageLoSidd; void* BapmVddCBaseLeakageHiSidd; } ;
struct vegam_smumgr {TYPE_1__ power_tune_table; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ smu_backend; } ;
struct phm_ppt_v1_information {struct phm_cac_tdp_table* cac_dtp_table; } ;
struct phm_cac_tdp_table {int usHighCACLeakage; int usLowCACLeakage; } ;

/* Variables and functions */
 void* CONVERT_FROM_HOST_TO_SMC_US (void*) ; 

__attribute__((used)) static int vegam_populate_bapm_vddc_base_leakage_sidd(struct pp_hwmgr *hwmgr)
{
	struct vegam_smumgr *smu_data = (struct vegam_smumgr *)(hwmgr->smu_backend);
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);
	uint16_t hi_sidd = smu_data->power_tune_table.BapmVddCBaseLeakageHiSidd;
	uint16_t lo_sidd = smu_data->power_tune_table.BapmVddCBaseLeakageLoSidd;
	struct phm_cac_tdp_table *cac_table = table_info->cac_dtp_table;

	hi_sidd = (uint16_t)(cac_table->usHighCACLeakage / 100 * 256);
	lo_sidd = (uint16_t)(cac_table->usLowCACLeakage / 100 * 256);

	smu_data->power_tune_table.BapmVddCBaseLeakageHiSidd =
			CONVERT_FROM_HOST_TO_SMC_US(hi_sidd);
	smu_data->power_tune_table.BapmVddCBaseLeakageLoSidd =
			CONVERT_FROM_HOST_TO_SMC_US(lo_sidd);

	return 0;
}