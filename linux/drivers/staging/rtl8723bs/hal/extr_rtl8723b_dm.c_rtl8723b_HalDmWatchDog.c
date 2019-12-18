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
typedef  int u8 ;
struct hal_com_data {int /*<<< orphan*/  odmpriv; } ;
struct adapter {int hw_init_completed; int /*<<< orphan*/  mlmepriv; } ;
struct TYPE_2__ {int bFwCurrentInPSMode; } ;

/* Variables and functions */
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int /*<<< orphan*/  HW_VAR_FWLPS_RF_ON ; 
 int /*<<< orphan*/  ODM_CMNINFO_BT_ENABLED ; 
 int /*<<< orphan*/  ODM_CMNINFO_LINK ; 
 int /*<<< orphan*/  ODM_CMNINFO_STATION_STATE ; 
 int /*<<< orphan*/  ODM_CmnInfoUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ODM_DMWatchdog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WIFI_STATION_STATE ; 
 TYPE_1__* adapter_to_pwrctl (struct adapter*) ; 
 scalar_t__ check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_CheckStatistics (struct adapter*) ; 
 int hal_btcoex_IsBtDisabled (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_check_rxfifo_full (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rtw_linked_check (struct adapter*) ; 

void rtl8723b_HalDmWatchDog(struct adapter *Adapter)
{
	bool bFwCurrentInPSMode = false;
	bool bFwPSAwake = true;
	u8 hw_init_completed = false;
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);

	hw_init_completed = Adapter->hw_init_completed;

	if (hw_init_completed == false)
		goto skip_dm;

	bFwCurrentInPSMode = adapter_to_pwrctl(Adapter)->bFwCurrentInPSMode;
	rtw_hal_get_hwreg(Adapter, HW_VAR_FWLPS_RF_ON, (u8 *)(&bFwPSAwake));

	if (
		(hw_init_completed == true) &&
		((!bFwCurrentInPSMode) && bFwPSAwake)
	) {
		/*  */
		/*  Calculate Tx/Rx statistics. */
		/*  */
		dm_CheckStatistics(Adapter);
		rtw_hal_check_rxfifo_full(Adapter);
	}

	/* ODM */
	if (hw_init_completed == true) {
		u8 bLinked = false;
		u8 bsta_state = false;
		bool bBtDisabled = true;

		if (rtw_linked_check(Adapter)) {
			bLinked = true;
			if (check_fwstate(&Adapter->mlmepriv, WIFI_STATION_STATE))
				bsta_state = true;
		}

		ODM_CmnInfoUpdate(&pHalData->odmpriv, ODM_CMNINFO_LINK, bLinked);
		ODM_CmnInfoUpdate(&pHalData->odmpriv, ODM_CMNINFO_STATION_STATE, bsta_state);

		/* ODM_CmnInfoUpdate(&pHalData->odmpriv , ODM_CMNINFO_RSSI_MIN, pdmpriv->MinUndecoratedPWDBForDM); */

		bBtDisabled = hal_btcoex_IsBtDisabled(Adapter);

		ODM_CmnInfoUpdate(&pHalData->odmpriv, ODM_CMNINFO_BT_ENABLED, ((bBtDisabled == true)?false:true));

		ODM_DMWatchdog(&pHalData->odmpriv);
	}

skip_dm:
	return;
}