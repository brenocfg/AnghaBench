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
typedef  scalar_t__ u8 ;
struct sta_info {int wireless_mode; int ra_mask; int /*<<< orphan*/  bw_mode; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  HW_VAR_RF_TYPE ; 
 scalar_t__ IsSupportedHT (int) ; 
 scalar_t__ IsSupportedVHT (int) ; 
 scalar_t__ RATEID_IDX_B ; 
 scalar_t__ RATEID_IDX_BG ; 
 scalar_t__ RATEID_IDX_BGN_20M_1SS_BN ; 
 scalar_t__ RATEID_IDX_BGN_20M_2SS_BN ; 
 scalar_t__ RATEID_IDX_BGN_40M_1SS ; 
 scalar_t__ RATEID_IDX_BGN_40M_2SS ; 
 scalar_t__ RATEID_IDX_G ; 
 scalar_t__ RATEID_IDX_GN_N1SS ; 
 scalar_t__ RATEID_IDX_GN_N2SS ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_2T2R ; 
#define  WIRELESS_11A 137 
#define  WIRELESS_11A_5N 136 
#define  WIRELESS_11B 135 
#define  WIRELESS_11BG 134 
#define  WIRELESS_11BG_24N 133 
#define  WIRELESS_11B_24N 132 
#define  WIRELESS_11G 131 
#define  WIRELESS_11G_24N 130 
#define  WIRELESS_11_24N 129 
#define  WIRELESS_11_5N 128 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 

u8 networktype_to_raid_ex(struct adapter *adapter, struct sta_info *psta)
{
	u8 raid, cur_rf_type, rf_type = RF_1T1R;

	rtw_hal_get_hwreg(adapter, HW_VAR_RF_TYPE, (u8 *)(&cur_rf_type));

	if (cur_rf_type == RF_1T1R) {
		rf_type = RF_1T1R;
	} else if (IsSupportedVHT(psta->wireless_mode)) {
		if (psta->ra_mask & 0xffc00000)
			rf_type = RF_2T2R;
	} else if (IsSupportedHT(psta->wireless_mode)) {
		if (psta->ra_mask & 0xfff00000)
			rf_type = RF_2T2R;
	}

	switch (psta->wireless_mode) {
	case WIRELESS_11B:
		raid = RATEID_IDX_B;
		break;
	case WIRELESS_11A:
	case WIRELESS_11G:
		raid = RATEID_IDX_G;
		break;
	case WIRELESS_11BG:
		raid = RATEID_IDX_BG;
		break;
	case WIRELESS_11_24N:
	case WIRELESS_11_5N:
	case WIRELESS_11A_5N:
	case WIRELESS_11G_24N:
		if (rf_type == RF_2T2R)
			raid = RATEID_IDX_GN_N2SS;
		else
			raid = RATEID_IDX_GN_N1SS;
		break;
	case WIRELESS_11B_24N:
	case WIRELESS_11BG_24N:
		if (psta->bw_mode == CHANNEL_WIDTH_20) {
			if (rf_type == RF_2T2R)
				raid = RATEID_IDX_BGN_20M_2SS_BN;
			else
				raid = RATEID_IDX_BGN_20M_1SS_BN;
		} else {
			if (rf_type == RF_2T2R)
				raid = RATEID_IDX_BGN_40M_2SS;
			else
				raid = RATEID_IDX_BGN_40M_1SS;
		}
		break;
	default:
		raid = RATEID_IDX_BGN_40M_2SS;
		break;
	}
	return raid;
}