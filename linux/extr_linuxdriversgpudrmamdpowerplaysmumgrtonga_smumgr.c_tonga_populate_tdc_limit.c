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
struct tonga_smumgr {TYPE_2__ power_tune_table; struct tonga_pt_defaults* power_tune_defaults; } ;
struct tonga_pt_defaults {int /*<<< orphan*/  tdc_mawt; int /*<<< orphan*/  tdc_vddc_throttle_release_limit_perc; } ;
struct pp_hwmgr {scalar_t__ pptable; scalar_t__ smu_backend; } ;
struct phm_ppt_v1_information {TYPE_1__* cac_dtp_table; } ;
struct TYPE_3__ {int usTDC; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_FROM_HOST_TO_SMC_US (scalar_t__) ; 

__attribute__((used)) static int tonga_populate_tdc_limit(struct pp_hwmgr *hwmgr)
{
	uint16_t tdc_limit;
	struct tonga_smumgr *smu_data =
				(struct tonga_smumgr *)(hwmgr->smu_backend);
	const struct tonga_pt_defaults *defaults = smu_data->power_tune_defaults;
	struct phm_ppt_v1_information *table_info =
			(struct phm_ppt_v1_information *)(hwmgr->pptable);

	/* TDC number of fraction bits are changed from 8 to 7
	 * for Fiji as requested by SMC team
	 */
	tdc_limit = (uint16_t)(table_info->cac_dtp_table->usTDC * 256);
	smu_data->power_tune_table.TDC_VDDC_PkgLimit =
			CONVERT_FROM_HOST_TO_SMC_US(tdc_limit);
	smu_data->power_tune_table.TDC_VDDC_ThrottleReleaseLimitPerc =
			defaults->tdc_vddc_throttle_release_limit_perc;
	smu_data->power_tune_table.TDC_MAWt = defaults->tdc_mawt;

	return 0;
}