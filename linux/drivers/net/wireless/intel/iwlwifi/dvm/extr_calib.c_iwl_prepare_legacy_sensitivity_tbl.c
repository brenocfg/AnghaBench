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
typedef  int /*<<< orphan*/  u16 ;
struct iwl_sensitivity_data {scalar_t__ nrg_th_cck; scalar_t__ auto_corr_cck_mrc; scalar_t__ auto_corr_cck; scalar_t__ nrg_th_ofdm; scalar_t__ auto_corr_ofdm_mrc_x1; scalar_t__ auto_corr_ofdm_x1; scalar_t__ auto_corr_ofdm_mrc; scalar_t__ auto_corr_ofdm; int /*<<< orphan*/  nrg_th_cca; int /*<<< orphan*/  barker_corr_th_min_mrc; int /*<<< orphan*/  barker_corr_th_min; } ;
struct iwl_priv {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 size_t HD_AUTO_CORR32_X1_TH_ADD_MIN_INDEX ; 
 size_t HD_AUTO_CORR32_X1_TH_ADD_MIN_MRC_INDEX ; 
 size_t HD_AUTO_CORR32_X4_TH_ADD_MIN_INDEX ; 
 size_t HD_AUTO_CORR32_X4_TH_ADD_MIN_MRC_INDEX ; 
 size_t HD_AUTO_CORR40_X4_TH_ADD_MIN_INDEX ; 
 size_t HD_AUTO_CORR40_X4_TH_ADD_MIN_MRC_INDEX ; 
 size_t HD_BARKER_CORR_TH_ADD_MIN_INDEX ; 
 size_t HD_BARKER_CORR_TH_ADD_MIN_MRC_INDEX ; 
 size_t HD_MIN_ENERGY_CCK_DET_INDEX ; 
 size_t HD_MIN_ENERGY_OFDM_DET_INDEX ; 
 size_t HD_OFDM_ENERGY_TH_IN_INDEX ; 
 int /*<<< orphan*/  IWL_DEBUG_CALIB (struct iwl_priv*,char*,scalar_t__,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_prepare_legacy_sensitivity_tbl(struct iwl_priv *priv,
				struct iwl_sensitivity_data *data,
				__le16 *tbl)
{
	tbl[HD_AUTO_CORR32_X4_TH_ADD_MIN_INDEX] =
				cpu_to_le16((u16)data->auto_corr_ofdm);
	tbl[HD_AUTO_CORR32_X4_TH_ADD_MIN_MRC_INDEX] =
				cpu_to_le16((u16)data->auto_corr_ofdm_mrc);
	tbl[HD_AUTO_CORR32_X1_TH_ADD_MIN_INDEX] =
				cpu_to_le16((u16)data->auto_corr_ofdm_x1);
	tbl[HD_AUTO_CORR32_X1_TH_ADD_MIN_MRC_INDEX] =
				cpu_to_le16((u16)data->auto_corr_ofdm_mrc_x1);

	tbl[HD_AUTO_CORR40_X4_TH_ADD_MIN_INDEX] =
				cpu_to_le16((u16)data->auto_corr_cck);
	tbl[HD_AUTO_CORR40_X4_TH_ADD_MIN_MRC_INDEX] =
				cpu_to_le16((u16)data->auto_corr_cck_mrc);

	tbl[HD_MIN_ENERGY_CCK_DET_INDEX] =
				cpu_to_le16((u16)data->nrg_th_cck);
	tbl[HD_MIN_ENERGY_OFDM_DET_INDEX] =
				cpu_to_le16((u16)data->nrg_th_ofdm);

	tbl[HD_BARKER_CORR_TH_ADD_MIN_INDEX] =
				cpu_to_le16(data->barker_corr_th_min);
	tbl[HD_BARKER_CORR_TH_ADD_MIN_MRC_INDEX] =
				cpu_to_le16(data->barker_corr_th_min_mrc);
	tbl[HD_OFDM_ENERGY_TH_IN_INDEX] =
				cpu_to_le16(data->nrg_th_cca);

	IWL_DEBUG_CALIB(priv, "ofdm: ac %u mrc %u x1 %u mrc_x1 %u thresh %u\n",
			data->auto_corr_ofdm, data->auto_corr_ofdm_mrc,
			data->auto_corr_ofdm_x1, data->auto_corr_ofdm_mrc_x1,
			data->nrg_th_ofdm);

	IWL_DEBUG_CALIB(priv, "cck: ac %u mrc %u thresh %u\n",
			data->auto_corr_cck, data->auto_corr_cck_mrc,
			data->nrg_th_cck);
}