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
typedef  int u8 ;
typedef  size_t u32 ;
struct sta_info {int dummy; } ;
struct rtw_dig {size_t AntDiv_RSSI_max; size_t RSSI_max; } ;
struct fast_ant_train {size_t* MainAnt_Cnt; size_t* MainAnt_Sum; size_t* AuxAnt_Cnt; size_t* AuxAnt_Sum; scalar_t__ RxIdleAnt; } ;
struct odm_dm_struct {scalar_t__ AntDivType; struct sta_info** pODM_StaInfo; struct rtw_dig DM_DigTable; struct fast_ant_train DM_FatTable; } ;

/* Variables and functions */
 scalar_t__ AUX_ANT ; 
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ IS_STA_VALID (struct sta_info*) ; 
 scalar_t__ MAIN_ANT ; 
 size_t ODM_ASSOCIATE_ENTRY_NUM ; 
 size_t max (size_t,size_t) ; 
 size_t min (size_t,size_t) ; 
 int /*<<< orphan*/  rtl88eu_dm_update_rx_idle_ant (struct odm_dm_struct*,int) ; 
 int /*<<< orphan*/  update_tx_ant_88eu (struct odm_dm_struct*,int,size_t) ; 

__attribute__((used)) static void rtl88eu_dm_hw_ant_div(struct odm_dm_struct *dm_odm)
{
	struct fast_ant_train *dm_fat_tbl = &dm_odm->DM_FatTable;
	struct rtw_dig *dig_table = &dm_odm->DM_DigTable;
	struct sta_info *entry;
	u32 i, min_rssi = 0xFF, ant_div_max_rssi = 0, max_rssi = 0;
	u32 local_min_rssi, local_max_rssi;
	u32 main_rssi, aux_rssi;
	u8 RxIdleAnt = 0, target_ant = 7;

	for (i = 0; i < ODM_ASSOCIATE_ENTRY_NUM; i++) {
		entry = dm_odm->pODM_StaInfo[i];
		if (IS_STA_VALID(entry)) {
			/* 2 Calculate RSSI per Antenna */
			main_rssi = (dm_fat_tbl->MainAnt_Cnt[i] != 0) ?
				     (dm_fat_tbl->MainAnt_Sum[i] /
				      dm_fat_tbl->MainAnt_Cnt[i]) : 0;
			aux_rssi = (dm_fat_tbl->AuxAnt_Cnt[i] != 0) ?
				    (dm_fat_tbl->AuxAnt_Sum[i] /
				     dm_fat_tbl->AuxAnt_Cnt[i]) : 0;
			target_ant = (main_rssi >= aux_rssi) ? MAIN_ANT : AUX_ANT;
			/* 2 Select max_rssi for DIG */
			local_max_rssi = max(main_rssi, aux_rssi);
			if ((local_max_rssi > ant_div_max_rssi) &&
			    (local_max_rssi < 40))
				ant_div_max_rssi = local_max_rssi;
			if (local_max_rssi > max_rssi)
				max_rssi = local_max_rssi;

			/* 2 Select RX Idle Antenna */
			if ((dm_fat_tbl->RxIdleAnt == MAIN_ANT) &&
			    (main_rssi == 0))
				main_rssi = aux_rssi;
			else if ((dm_fat_tbl->RxIdleAnt == AUX_ANT) &&
				 (aux_rssi == 0))
				aux_rssi = main_rssi;

			local_min_rssi = min(main_rssi, aux_rssi);
			if (local_min_rssi < min_rssi) {
				min_rssi = local_min_rssi;
				RxIdleAnt = target_ant;
			}
			/* 2 Select TRX Antenna */
			if (dm_odm->AntDivType == CG_TRX_HW_ANTDIV)
				update_tx_ant_88eu(dm_odm, target_ant, i);
		}
		dm_fat_tbl->MainAnt_Sum[i] = 0;
		dm_fat_tbl->AuxAnt_Sum[i] = 0;
		dm_fat_tbl->MainAnt_Cnt[i] = 0;
		dm_fat_tbl->AuxAnt_Cnt[i] = 0;
	}

	/* 2 Set RX Idle Antenna */
	rtl88eu_dm_update_rx_idle_ant(dm_odm, RxIdleAnt);

	dig_table->AntDiv_RSSI_max = ant_div_max_rssi;
	dig_table->RSSI_max = max_rssi;
}