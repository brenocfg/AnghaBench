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
typedef  int uint32_t ;
struct vega10_hwmgr {int acg_loop_state; TYPE_1__* smu_features; } ;
struct pp_hwmgr {struct vega10_hwmgr* backend; } ;
struct TYPE_2__ {int enabled; int /*<<< orphan*/  smu_feature_bitmap; scalar_t__ supported; } ;

/* Variables and functions */
 size_t GNLD_ACG ; 
 size_t GNLD_DPM_PREFETCHER ; 
 int /*<<< orphan*/  PPSMC_MSG_InitializeAcg ; 
 int /*<<< orphan*/  PPSMC_MSG_RunAcgBtc ; 
 int /*<<< orphan*/  PPSMC_MSG_RunAcgInClosedLoop ; 
 int /*<<< orphan*/  PPSMC_MSG_RunAcgInOpenLoop ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int smum_get_argument (struct pp_hwmgr*) ; 
 int /*<<< orphan*/  smum_send_msg_to_smc (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 
 scalar_t__ vega10_enable_smc_features (struct pp_hwmgr*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vega10_acg_enable(struct pp_hwmgr *hwmgr)
{
	struct vega10_hwmgr *data = hwmgr->backend;
	uint32_t agc_btc_response;

	if (data->smu_features[GNLD_ACG].supported) {
		if (0 == vega10_enable_smc_features(hwmgr, true,
					data->smu_features[GNLD_DPM_PREFETCHER].smu_feature_bitmap))
			data->smu_features[GNLD_DPM_PREFETCHER].enabled = true;

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_InitializeAcg);

		smum_send_msg_to_smc(hwmgr, PPSMC_MSG_RunAcgBtc);
		agc_btc_response = smum_get_argument(hwmgr);

		if (1 == agc_btc_response) {
			if (1 == data->acg_loop_state)
				smum_send_msg_to_smc(hwmgr, PPSMC_MSG_RunAcgInClosedLoop);
			else if (2 == data->acg_loop_state)
				smum_send_msg_to_smc(hwmgr, PPSMC_MSG_RunAcgInOpenLoop);
			if (0 == vega10_enable_smc_features(hwmgr, true,
				data->smu_features[GNLD_ACG].smu_feature_bitmap))
					data->smu_features[GNLD_ACG].enabled = true;
		} else {
			pr_info("[ACG_Enable] ACG BTC Returned Failed Status!\n");
			data->smu_features[GNLD_ACG].enabled = false;
		}
	}

	return 0;
}