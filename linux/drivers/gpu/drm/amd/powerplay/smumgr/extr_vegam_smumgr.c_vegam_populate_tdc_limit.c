#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  TDC_MAWt; int /*<<< orphan*/  TDC_VDDC_ThrottleReleaseLimitPerc; int /*<<< orphan*/  TDC_VDDC_PkgLimit; } ;
struct vegam_smumgr {TYPE_2__ power_tune_table; struct vegam_pt_defaults* power_tune_defaults; } ;
struct vegam_pt_defaults {int /*<<< orphan*/  TDC_MAWt; int /*<<< orphan*/  TDC_VDDC_ThrottleReleaseLimitPerc; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ smu_backend; } ;
struct phm_ppt_v1_information {TYPE_1__* cac_dtp_table; } ;
struct TYPE_3__ {int usTDC; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_FROM_HOST_TO_SMC_US (scalar_t__) ; 

__attribute__((used)) static int vegam_populate_tdc_limit(struct pp_hwmgr *hwmgr)
{
	uint16_t tdc_limit;
	struct vegam_smumgr *smu_data = (struct vegam_smumgr *)(hwmgr->smu_backend);
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);
	const struct vegam_pt_defaults *defaults = smu_data->power_tune_defaults;

	tdc_limit = (uint16_t)(table_info->cac_dtp_table->usTDC * 128);
	smu_data->power_tune_table.TDC_VDDC_PkgLimit =
			CONVERT_FROM_HOST_TO_SMC_US(tdc_limit);
	smu_data->power_tune_table.TDC_VDDC_ThrottleReleaseLimitPerc =
			defaults->TDC_VDDC_ThrottleReleaseLimitPerc;
	smu_data->power_tune_table.TDC_MAWt = defaults->TDC_MAWt;

	return 0;
}