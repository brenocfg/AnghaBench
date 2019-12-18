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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {scalar_t__ reloadtxpowerindex; } ;
struct rtl_efuse {int eeprom_thermalmeter; } ;
struct rtl_dm {int txpower_trackinginit; int swing_idx_cck_base; int* swing_idx_ofdm_base; size_t* thermalvalue_avg; size_t thermalvalue_avg_index; size_t thermalvalue; size_t thermalvalue_lck; size_t thermalvalue_iqk; size_t* delta_power_index_last; size_t* delta_power_index; size_t* absolute_ofdm_swing_idx; scalar_t__* power_index_offset; int* ofdm_index; int cck_index; int swing_idx_cck; int* swing_idx_ofdm; int /*<<< orphan*/  txpower_track_control; int /*<<< orphan*/  default_ofdm_index; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 size_t AVG_THERMAL_NUM_8812A ; 
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 size_t IQK_THRESHOLD ; 
 size_t MAX_PATH_NUM_8812A ; 
 int /*<<< orphan*/  MIX_MODE ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_B ; 
 int /*<<< orphan*/  RF_T_METER_8812A ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 size_t TXPWR_TRACK_TABLE_SIZE ; 
 int TXSCALE_TABLE_SIZE ; 
 int /*<<< orphan*/  rtl8812ae_dm_txpwr_track_set_pwr (struct ieee80211_hw*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  rtl8812ae_do_iqk (struct ieee80211_hw*,size_t,size_t,int) ; 
 int /*<<< orphan*/  rtl8812ae_get_delta_swing_table (struct ieee80211_hw*,size_t**,size_t**,size_t**,size_t**) ; 
 int /*<<< orphan*/  rtl8821ae_phy_lc_calibrate (struct ieee80211_hw*) ; 
 struct rtl_dm* rtl_dm (struct rtl_priv*) ; 
 struct rtl_efuse* rtl_efuse (struct rtl_priv*) ; 
 scalar_t__ rtl_get_rfreg (struct ieee80211_hw*,size_t,int /*<<< orphan*/ ,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl8812ae_dm_txpower_tracking_callback_thermalmeter(
	struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct rtl_dm	*rtldm = rtl_dm(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	u8 thermal_value = 0, delta, delta_lck, delta_iqk, p = 0, i = 0;
	u8 thermal_value_avg_count = 0;
	u32 thermal_value_avg = 0;
	/* OFDM BB Swing should be less than +3.0dB, */
	u8 ofdm_min_index = 6;
	 /* GetRightChnlPlaceforIQK(pHalData->CurrentChannel)*/
	u8 index_for_channel = 0;
	/* 1. The following TWO tables decide
	 * the final index of OFDM/CCK swing table.
	 */
	u8 *delta_swing_table_idx_tup_a;
	u8 *delta_swing_table_idx_tdown_a;
	u8 *delta_swing_table_idx_tup_b;
	u8 *delta_swing_table_idx_tdown_b;

	/*2. Initilization ( 7 steps in total )*/
	rtl8812ae_get_delta_swing_table(hw,
		(u8 **)&delta_swing_table_idx_tup_a,
		(u8 **)&delta_swing_table_idx_tdown_a,
		(u8 **)&delta_swing_table_idx_tup_b,
		(u8 **)&delta_swing_table_idx_tdown_b);

	rtldm->txpower_trackinginit = true;

	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "pDM_Odm->BbSwingIdxCckBase: %d, pDM_Odm->BbSwingIdxOfdmBase[A]:%d, pDM_Odm->DefaultOfdmIndex: %d\n",
		 rtldm->swing_idx_cck_base,
		 rtldm->swing_idx_ofdm_base[RF90_PATH_A],
		 rtldm->default_ofdm_index);

	thermal_value = (u8)rtl_get_rfreg(hw, RF90_PATH_A,
		/*0x42: RF Reg[15:10] 88E*/
		RF_T_METER_8812A, 0xfc00);
	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "Thermal Meter = 0x%X, EFUSE Thermal Base = 0x%X\n",
		 thermal_value, rtlefuse->eeprom_thermalmeter);
	if (!rtldm->txpower_track_control ||
	    rtlefuse->eeprom_thermalmeter == 0 ||
	    rtlefuse->eeprom_thermalmeter == 0xFF)
		return;

	/* 3. Initialize ThermalValues of RFCalibrateInfo*/

	if (rtlhal->reloadtxpowerindex)
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "reload ofdm index for band switch\n");

	/*4. Calculate average thermal meter*/
	rtldm->thermalvalue_avg[rtldm->thermalvalue_avg_index] = thermal_value;
	rtldm->thermalvalue_avg_index++;
	if (rtldm->thermalvalue_avg_index == AVG_THERMAL_NUM_8812A)
		/*Average times =  c.AverageThermalNum*/
		rtldm->thermalvalue_avg_index = 0;

	for (i = 0; i < AVG_THERMAL_NUM_8812A; i++) {
		if (rtldm->thermalvalue_avg[i]) {
			thermal_value_avg += rtldm->thermalvalue_avg[i];
			thermal_value_avg_count++;
		}
	}
	/*Calculate Average ThermalValue after average enough times*/
	if (thermal_value_avg_count) {
		thermal_value = (u8)(thermal_value_avg /
				thermal_value_avg_count);
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "AVG Thermal Meter = 0x%X, EFUSE Thermal Base = 0x%X\n",
			 thermal_value, rtlefuse->eeprom_thermalmeter);
	}

	/*5. Calculate delta, delta_LCK, delta_IQK.
	 *"delta" here is used to determine whether
	 *thermal value changes or not.
	 */
	delta = (thermal_value > rtldm->thermalvalue) ?
		(thermal_value - rtldm->thermalvalue) :
		(rtldm->thermalvalue - thermal_value);
	delta_lck = (thermal_value > rtldm->thermalvalue_lck) ?
		(thermal_value - rtldm->thermalvalue_lck) :
		(rtldm->thermalvalue_lck - thermal_value);
	delta_iqk = (thermal_value > rtldm->thermalvalue_iqk) ?
		(thermal_value - rtldm->thermalvalue_iqk) :
		(rtldm->thermalvalue_iqk - thermal_value);

	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "(delta, delta_LCK, delta_IQK) = (%d, %d, %d)\n",
		 delta, delta_lck, delta_iqk);

	/* 6. If necessary, do LCK.
	 * Delta temperature is equal to or larger than 20 centigrade.
	 */
	if (delta_lck >= IQK_THRESHOLD) {
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "delta_LCK(%d) >= Threshold_IQK(%d)\n",
			 delta_lck, IQK_THRESHOLD);
		rtldm->thermalvalue_lck = thermal_value;
		rtl8821ae_phy_lc_calibrate(hw);
	}

	/*7. If necessary, move the index of swing table to adjust Tx power.*/

	if (delta > 0 && rtldm->txpower_track_control) {
		/* "delta" here is used to record the
		 * absolute value of differrence.
		 */
		delta = thermal_value > rtlefuse->eeprom_thermalmeter ?
			(thermal_value - rtlefuse->eeprom_thermalmeter) :
			(rtlefuse->eeprom_thermalmeter - thermal_value);

		if (delta >= TXPWR_TRACK_TABLE_SIZE)
			delta = TXPWR_TRACK_TABLE_SIZE - 1;

		/*7.1 The Final Power Index = BaseIndex + PowerIndexOffset*/

		if (thermal_value > rtlefuse->eeprom_thermalmeter) {
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "delta_swing_table_idx_tup_a[%d] = %d\n",
				 delta, delta_swing_table_idx_tup_a[delta]);
			rtldm->delta_power_index_last[RF90_PATH_A] =
				rtldm->delta_power_index[RF90_PATH_A];
			rtldm->delta_power_index[RF90_PATH_A] =
				delta_swing_table_idx_tup_a[delta];

			rtldm->absolute_ofdm_swing_idx[RF90_PATH_A] =
				delta_swing_table_idx_tup_a[delta];
			/*Record delta swing for mix mode power tracking*/

			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "******Temp is higher and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A] = %d\n",
			rtldm->absolute_ofdm_swing_idx[RF90_PATH_A]);

			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "delta_swing_table_idx_tup_b[%d] = %d\n",
				 delta, delta_swing_table_idx_tup_b[delta]);
			rtldm->delta_power_index_last[RF90_PATH_B] =
				rtldm->delta_power_index[RF90_PATH_B];
			rtldm->delta_power_index[RF90_PATH_B] =
				delta_swing_table_idx_tup_b[delta];

			rtldm->absolute_ofdm_swing_idx[RF90_PATH_B] =
				delta_swing_table_idx_tup_b[delta];
			/*Record delta swing for mix mode power tracking*/

			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "******Temp is higher and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_B] = %d\n",
				 rtldm->absolute_ofdm_swing_idx[RF90_PATH_B]);
		} else {
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "delta_swing_table_idx_tdown_a[%d] = %d\n",
				 delta, delta_swing_table_idx_tdown_a[delta]);

			rtldm->delta_power_index_last[RF90_PATH_A] =
				rtldm->delta_power_index[RF90_PATH_A];
			rtldm->delta_power_index[RF90_PATH_A] =
				-1 * delta_swing_table_idx_tdown_a[delta];

			rtldm->absolute_ofdm_swing_idx[RF90_PATH_A] =
				-1 * delta_swing_table_idx_tdown_a[delta];
			/* Record delta swing for mix mode power tracking*/
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "******Temp is lower and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_A] = %d\n",
				 rtldm->absolute_ofdm_swing_idx[RF90_PATH_A]);

			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "deltaSwingTableIdx_TDOWN_B[%d] = %d\n",
				 delta, delta_swing_table_idx_tdown_b[delta]);

			rtldm->delta_power_index_last[RF90_PATH_B] =
				rtldm->delta_power_index[RF90_PATH_B];
			rtldm->delta_power_index[RF90_PATH_B] =
				-1 * delta_swing_table_idx_tdown_b[delta];

			rtldm->absolute_ofdm_swing_idx[RF90_PATH_B] =
				-1 * delta_swing_table_idx_tdown_b[delta];
			/*Record delta swing for mix mode power tracking*/

			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "******Temp is lower and pDM_Odm->Absolute_OFDMSwingIdx[ODM_RF_PATH_B] = %d\n",
				 rtldm->absolute_ofdm_swing_idx[RF90_PATH_B]);
		}

		for (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++) {
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "============================= [Path-%c]Calculating PowerIndexOffset =============================\n",
				 (p == RF90_PATH_A ? 'A' : 'B'));

			if (rtldm->delta_power_index[p] ==
				rtldm->delta_power_index_last[p])
				/*If Thermal value changes but lookup
				table value still the same*/
				rtldm->power_index_offset[p] = 0;
			else
				rtldm->power_index_offset[p] =
					rtldm->delta_power_index[p] -
					rtldm->delta_power_index_last[p];
				/* Power Index Diff between 2
				 * times Power Tracking
				 */
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "[Path-%c] PowerIndexOffset(%d) =DeltaPowerIndex(%d) -DeltaPowerIndexLast(%d)\n",
				 (p == RF90_PATH_A ? 'A' : 'B'),
				 rtldm->power_index_offset[p],
				 rtldm->delta_power_index[p] ,
				 rtldm->delta_power_index_last[p]);

			rtldm->ofdm_index[p] =
					rtldm->swing_idx_ofdm_base[p] +
					rtldm->power_index_offset[p];
			rtldm->cck_index =
					rtldm->swing_idx_cck_base +
					rtldm->power_index_offset[p];

			rtldm->swing_idx_cck = rtldm->cck_index;
			rtldm->swing_idx_ofdm[p] = rtldm->ofdm_index[p];

			/****Print BB Swing Base and Index Offset */

			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "The 'CCK' final index(%d) = BaseIndex(%d) + PowerIndexOffset(%d)\n",
				 rtldm->swing_idx_cck,
				rtldm->swing_idx_cck_base,
				rtldm->power_index_offset[p]);
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "The 'OFDM' final index(%d) = BaseIndex[%c](%d) + PowerIndexOffset(%d)\n",
				 rtldm->swing_idx_ofdm[p],
				 (p == RF90_PATH_A ? 'A' : 'B'),
				 rtldm->swing_idx_ofdm_base[p],
				 rtldm->power_index_offset[p]);

			/*7.1 Handle boundary conditions of index.*/

			if (rtldm->ofdm_index[p] > TXSCALE_TABLE_SIZE - 1)
				rtldm->ofdm_index[p] = TXSCALE_TABLE_SIZE - 1;
			else if (rtldm->ofdm_index[p] < ofdm_min_index)
				rtldm->ofdm_index[p] = ofdm_min_index;
		}
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "\n\n====================================================================================\n");
		if (rtldm->cck_index > TXSCALE_TABLE_SIZE - 1)
			rtldm->cck_index = TXSCALE_TABLE_SIZE - 1;
		else if (rtldm->cck_index < 0)
			rtldm->cck_index = 0;
	} else {
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "The thermal meter is unchanged or TxPowerTracking OFF(%d): ThermalValue: %d , pDM_Odm->RFCalibrateInfo.ThermalValue: %d\n",
			 rtldm->txpower_track_control,
			 thermal_value,
			 rtldm->thermalvalue);

		for (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++)
			rtldm->power_index_offset[p] = 0;
	}
	/*Print Swing base & current*/
	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "TxPowerTracking: [CCK] Swing Current Index: %d,Swing Base Index: %d\n",
		 rtldm->cck_index, rtldm->swing_idx_cck_base);
	for (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++) {
		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "TxPowerTracking: [OFDM] Swing Current Index: %d,Swing Base Index[%c]: %d\n",
			 rtldm->ofdm_index[p],
			 (p == RF90_PATH_A ? 'A' : 'B'),
			 rtldm->swing_idx_ofdm_base[p]);
	}

	if ((rtldm->power_index_offset[RF90_PATH_A] != 0 ||
		rtldm->power_index_offset[RF90_PATH_B] != 0) &&
		rtldm->txpower_track_control) {
		/*7.2 Configure the Swing Table to adjust Tx Power.
		 *Always TRUE after Tx Power is adjusted by power tracking.
		 *
		 *2012/04/23 MH According to Luke's suggestion,
		 *we can not write BB digital
		 *to increase TX power. Otherwise, EVM will be bad.
		 *
		 *2012/04/25 MH Add for tx power tracking to set
		 *tx power in tx agc for 88E.
		 */
		if (thermal_value > rtldm->thermalvalue) {
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "Temperature Increasing(A): delta_pi: %d , delta_t: %d, Now_t: %d,EFUSE_t: %d, Last_t: %d\n",
				 rtldm->power_index_offset[RF90_PATH_A],
				 delta, thermal_value,
				 rtlefuse->eeprom_thermalmeter,
				 rtldm->thermalvalue);

			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "Temperature Increasing(B): delta_pi: %d ,delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
				 rtldm->power_index_offset[RF90_PATH_B],
				 delta, thermal_value,
				 rtlefuse->eeprom_thermalmeter,
				 rtldm->thermalvalue);
		} else if (thermal_value < rtldm->thermalvalue) { /*Low temperature*/
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "Temperature Decreasing(A): delta_pi: %d , delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
				 rtldm->power_index_offset[RF90_PATH_A],
				 delta, thermal_value,
				 rtlefuse->eeprom_thermalmeter,
				 rtldm->thermalvalue);

			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "Temperature Decreasing(B): delta_pi: %d , delta_t: %d, Now_t: %d, EFUSE_t: %d, Last_t: %d\n",
				 rtldm->power_index_offset[RF90_PATH_B],
				 delta, thermal_value,
				 rtlefuse->eeprom_thermalmeter,
				 rtldm->thermalvalue);
		}

		if (thermal_value > rtlefuse->eeprom_thermalmeter) {
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "Temperature(%d) higher than PG value(%d)\n",
				 thermal_value, rtlefuse->eeprom_thermalmeter);

			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "**********Enter POWER Tracking MIX_MODE**********\n");
			for (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++)
				rtl8812ae_dm_txpwr_track_set_pwr(hw, MIX_MODE,
								 p, 0);
		} else {
			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "Temperature(%d) lower than PG value(%d)\n",
				 thermal_value, rtlefuse->eeprom_thermalmeter);

			RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
				 "**********Enter POWER Tracking MIX_MODE**********\n");
			for (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++)
				rtl8812ae_dm_txpwr_track_set_pwr(hw, MIX_MODE,
								 p, index_for_channel);
		}
		/*Record last time Power Tracking result as base.*/
		rtldm->swing_idx_cck_base = rtldm->swing_idx_cck;
		for (p = RF90_PATH_A; p < MAX_PATH_NUM_8812A; p++)
				rtldm->swing_idx_ofdm_base[p] =
					rtldm->swing_idx_ofdm[p];

		RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
			 "pDM_Odm->RFCalibrateInfo.ThermalValue =%d ThermalValue= %d\n",
			 rtldm->thermalvalue, thermal_value);
		/*Record last Power Tracking Thermal Value*/
		rtldm->thermalvalue = thermal_value;
	}
	/*Delta temperature is equal to or larger than
	20 centigrade (When threshold is 8).*/
	if (delta_iqk >= IQK_THRESHOLD)
		rtl8812ae_do_iqk(hw, delta_iqk, thermal_value, 8);

	RT_TRACE(rtlpriv, COMP_POWER_TRACKING, DBG_LOUD,
		 "<===rtl8812ae_dm_txpower_tracking_callback_thermalmeter\n");
}