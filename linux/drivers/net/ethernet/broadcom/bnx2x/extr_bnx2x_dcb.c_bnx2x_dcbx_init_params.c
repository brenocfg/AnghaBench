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
struct TYPE_4__ {int admin_dcbx_version; int admin_ets_willing; int admin_pfc_willing; int overwrite_settings; int admin_ets_enable; int admin_pfc_enable; int admin_tc_supported_tx_enable; int admin_ets_configuration_tx_enable; int admin_pfc_tx_enable; int admin_application_priority_tx_enable; int admin_ets_reco_valid; int admin_app_priority_willing; int* admin_configuration_bw_precentage; int* admin_recommendation_bw_precentage; int* admin_recommendation_ets_pg; int admin_pfc_bitmap; scalar_t__ admin_default_priority; TYPE_1__* admin_priority_app_table; scalar_t__* admin_configuration_ets_pg; } ;
struct bnx2x {TYPE_2__ dcbx_config_params; } ;
struct TYPE_3__ {scalar_t__ valid; } ;

/* Variables and functions */

void bnx2x_dcbx_init_params(struct bnx2x *bp)
{
	bp->dcbx_config_params.admin_dcbx_version = 0x0; /* 0 - CEE; 1 - IEEE */
	bp->dcbx_config_params.admin_ets_willing = 1;
	bp->dcbx_config_params.admin_pfc_willing = 1;
	bp->dcbx_config_params.overwrite_settings = 1;
	bp->dcbx_config_params.admin_ets_enable = 1;
	bp->dcbx_config_params.admin_pfc_enable = 1;
	bp->dcbx_config_params.admin_tc_supported_tx_enable = 1;
	bp->dcbx_config_params.admin_ets_configuration_tx_enable = 1;
	bp->dcbx_config_params.admin_pfc_tx_enable = 1;
	bp->dcbx_config_params.admin_application_priority_tx_enable = 1;
	bp->dcbx_config_params.admin_ets_reco_valid = 1;
	bp->dcbx_config_params.admin_app_priority_willing = 1;
	bp->dcbx_config_params.admin_configuration_bw_precentage[0] = 100;
	bp->dcbx_config_params.admin_configuration_bw_precentage[1] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[2] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[3] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[4] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[5] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[6] = 0;
	bp->dcbx_config_params.admin_configuration_bw_precentage[7] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[0] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[1] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[2] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[3] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[4] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[5] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[6] = 0;
	bp->dcbx_config_params.admin_configuration_ets_pg[7] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[0] = 100;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[1] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[2] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[3] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[4] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[5] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[6] = 0;
	bp->dcbx_config_params.admin_recommendation_bw_precentage[7] = 0;
	bp->dcbx_config_params.admin_recommendation_ets_pg[0] = 0;
	bp->dcbx_config_params.admin_recommendation_ets_pg[1] = 1;
	bp->dcbx_config_params.admin_recommendation_ets_pg[2] = 2;
	bp->dcbx_config_params.admin_recommendation_ets_pg[3] = 3;
	bp->dcbx_config_params.admin_recommendation_ets_pg[4] = 4;
	bp->dcbx_config_params.admin_recommendation_ets_pg[5] = 5;
	bp->dcbx_config_params.admin_recommendation_ets_pg[6] = 6;
	bp->dcbx_config_params.admin_recommendation_ets_pg[7] = 7;
	bp->dcbx_config_params.admin_pfc_bitmap = 0x0;
	bp->dcbx_config_params.admin_priority_app_table[0].valid = 0;
	bp->dcbx_config_params.admin_priority_app_table[1].valid = 0;
	bp->dcbx_config_params.admin_priority_app_table[2].valid = 0;
	bp->dcbx_config_params.admin_priority_app_table[3].valid = 0;
	bp->dcbx_config_params.admin_default_priority = 0;
}