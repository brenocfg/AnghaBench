#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sta_priv {int dummy; } ;
struct TYPE_5__ {scalar_t__ UndecoratedSmoothedPWDB; } ;
struct sta_info {TYPE_1__ rssi_stat; } ;
struct mlme_priv {int dummy; } ;
struct TYPE_6__ {int CurIGValue; } ;
struct TYPE_7__ {int SupportAbility; scalar_t__ RSSI_Min; TYPE_2__ DM_DigTable; } ;
struct dm_priv {scalar_t__ EntryMinUndecoratedSmoothedPWDB; scalar_t__ MinUndecoratedPWDBForDM; } ;
struct hal_com_data {TYPE_3__ odmpriv; struct dm_priv dmpriv; } ;
struct adapter {int hw_init_completed; struct sta_priv stapriv; struct mlme_priv mlmepriv; } ;
typedef  TYPE_2__* pDIG_T ;
typedef  TYPE_3__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int,scalar_t__) ; 
 struct hal_com_data* GET_HAL_DATA (struct adapter*) ; 
 int ODM_BB_RSSI_MONITOR ; 
 int /*<<< orphan*/  ODM_CMNINFO_LINK ; 
 int /*<<< orphan*/  ODM_CmnInfoUpdate (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_bssid (struct mlme_priv*) ; 
 int /*<<< orphan*/  rtw_dm_in_lps_wk_cmd (struct adapter*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_linked_check (struct adapter*) ; 

void rtl8723b_HalDmWatchDog_in_LPS(struct adapter *Adapter)
{
	u8 bLinked = false;
	struct hal_com_data *pHalData = GET_HAL_DATA(Adapter);
	struct mlme_priv *pmlmepriv = &Adapter->mlmepriv;
	struct dm_priv *pdmpriv = &pHalData->dmpriv;
	PDM_ODM_T pDM_Odm = &pHalData->odmpriv;
	pDIG_T pDM_DigTable = &pDM_Odm->DM_DigTable;
	struct sta_priv *pstapriv = &Adapter->stapriv;
	struct sta_info *psta = NULL;

	if (Adapter->hw_init_completed == false)
		goto skip_lps_dm;


	if (rtw_linked_check(Adapter))
		bLinked = true;

	ODM_CmnInfoUpdate(&pHalData->odmpriv, ODM_CMNINFO_LINK, bLinked);

	if (bLinked == false)
		goto skip_lps_dm;

	if (!(pDM_Odm->SupportAbility & ODM_BB_RSSI_MONITOR))
		goto skip_lps_dm;


	/* ODM_DMWatchdog(&pHalData->odmpriv); */
	/* Do DIG by RSSI In LPS-32K */

      /* 1 Find MIN-RSSI */
	psta = rtw_get_stainfo(pstapriv, get_bssid(pmlmepriv));
	if (!psta)
		goto skip_lps_dm;

	pdmpriv->EntryMinUndecoratedSmoothedPWDB = psta->rssi_stat.UndecoratedSmoothedPWDB;

	DBG_871X("CurIGValue =%d, EntryMinUndecoratedSmoothedPWDB = %d\n", pDM_DigTable->CurIGValue, pdmpriv->EntryMinUndecoratedSmoothedPWDB);

	if (pdmpriv->EntryMinUndecoratedSmoothedPWDB <= 0)
		goto skip_lps_dm;

	pdmpriv->MinUndecoratedPWDBForDM = pdmpriv->EntryMinUndecoratedSmoothedPWDB;

	pDM_Odm->RSSI_Min = pdmpriv->MinUndecoratedPWDBForDM;

	/* if (pDM_DigTable->CurIGValue != pDM_Odm->RSSI_Min) */
	if (
		(pDM_DigTable->CurIGValue > pDM_Odm->RSSI_Min + 5) ||
		(pDM_DigTable->CurIGValue < pDM_Odm->RSSI_Min - 5)
	)
		rtw_dm_in_lps_wk_cmd(Adapter);


skip_lps_dm:

	return;

}