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
struct rtw_dig {scalar_t__ CurIGValue; scalar_t__ DIG_Dynamic_MIN_0; scalar_t__ rx_gain_range_max; int LargeFAHit; scalar_t__ ForbiddenIGI; int rx_gain_range_min; int Recover_cnt; scalar_t__ bMediaConnect_0; scalar_t__ AntDiv_RSSI_max; } ;
struct false_alarm_stats {int Cnt_all; } ;
struct odm_dm_struct {int SupportAbility; scalar_t__ RSSI_Min; scalar_t__ AntDivType; scalar_t__ bLinked; scalar_t__ bOneEntryOnly; int /*<<< orphan*/  bDMInitialGainEnable; scalar_t__* pbScanInProcess; struct false_alarm_stats FalseAlmCnt; struct rtw_dig DM_DigTable; } ;

/* Variables and functions */
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 int DM_DIG_FA_TH0 ; 
 int DM_DIG_FA_TH1 ; 
 int DM_DIG_FA_TH2 ; 
 scalar_t__ DM_DIG_MAX_AP ; 
 scalar_t__ DM_DIG_MAX_NIC ; 
 scalar_t__ DM_DIG_MIN_NIC ; 
 int ODM_BB_ANT_DIV ; 
 int ODM_BB_DIG ; 
 int ODM_BB_FA_CNT ; 
 int /*<<< orphan*/  ODM_COMP_ANT_DIV ; 
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ODM_Write_DIG (struct odm_dm_struct*,scalar_t__) ; 

void odm_DIG(struct odm_dm_struct *pDM_Odm)
{
	struct rtw_dig *pDM_DigTable = &pDM_Odm->DM_DigTable;
	struct false_alarm_stats *pFalseAlmCnt = &pDM_Odm->FalseAlmCnt;
	u8 DIG_Dynamic_MIN;
	u8 DIG_MaxOfMin;
	bool FirstConnect, FirstDisConnect;
	u8 dm_dig_max, dm_dig_min;
	u8 CurrentIGI = pDM_DigTable->CurIGValue;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG()==>\n"));
	if ((!(pDM_Odm->SupportAbility&ODM_BB_DIG)) || (!(pDM_Odm->SupportAbility&ODM_BB_FA_CNT))) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD,
			     ("odm_DIG() Return: SupportAbility ODM_BB_DIG or ODM_BB_FA_CNT is disabled\n"));
		return;
	}

	if (*(pDM_Odm->pbScanInProcess)) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG() Return: In Scan Progress\n"));
		return;
	}

	/* add by Neil Chen to avoid PSD is processing */
	if (!pDM_Odm->bDMInitialGainEnable) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG() Return: PSD is Processing\n"));
		return;
	}

	DIG_Dynamic_MIN = pDM_DigTable->DIG_Dynamic_MIN_0;
	FirstConnect = (pDM_Odm->bLinked) && (!pDM_DigTable->bMediaConnect_0);
	FirstDisConnect = (!pDM_Odm->bLinked) && (pDM_DigTable->bMediaConnect_0);

	/* 1 Boundary Decision */
	dm_dig_max = DM_DIG_MAX_NIC;
	dm_dig_min = DM_DIG_MIN_NIC;
	DIG_MaxOfMin = DM_DIG_MAX_AP;

	if (pDM_Odm->bLinked) {
		/* 2 Modify DIG upper bound */
		if ((pDM_Odm->RSSI_Min + 20) > dm_dig_max)
			pDM_DigTable->rx_gain_range_max = dm_dig_max;
		else if ((pDM_Odm->RSSI_Min + 20) < dm_dig_min)
			pDM_DigTable->rx_gain_range_max = dm_dig_min;
		else
			pDM_DigTable->rx_gain_range_max = pDM_Odm->RSSI_Min + 20;
		/* 2 Modify DIG lower bound */
		if (pDM_Odm->bOneEntryOnly) {
			if (pDM_Odm->RSSI_Min < dm_dig_min)
				DIG_Dynamic_MIN = dm_dig_min;
			else if (pDM_Odm->RSSI_Min > DIG_MaxOfMin)
				DIG_Dynamic_MIN = DIG_MaxOfMin;
			else
				DIG_Dynamic_MIN = pDM_Odm->RSSI_Min;
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD,
				     ("odm_DIG() : bOneEntryOnly=true,  DIG_Dynamic_MIN=0x%x\n",
				     DIG_Dynamic_MIN));
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD,
				     ("odm_DIG() : pDM_Odm->RSSI_Min=%d\n",
				     pDM_Odm->RSSI_Min));
		} else if (pDM_Odm->SupportAbility & ODM_BB_ANT_DIV) {
			/* 1 Lower Bound for 88E AntDiv */
			if (pDM_Odm->AntDivType == CG_TRX_HW_ANTDIV) {
				DIG_Dynamic_MIN = (u8)pDM_DigTable->AntDiv_RSSI_max;
				ODM_RT_TRACE(pDM_Odm, ODM_COMP_ANT_DIV, ODM_DBG_LOUD,
					     ("odm_DIG(): pDM_DigTable->AntDiv_RSSI_max=%d\n",
					     pDM_DigTable->AntDiv_RSSI_max));
			}
		} else {
			DIG_Dynamic_MIN = dm_dig_min;
		}
	} else {
		pDM_DigTable->rx_gain_range_max = dm_dig_max;
		DIG_Dynamic_MIN = dm_dig_min;
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG() : No Link\n"));
	}

	/* 1 Modify DIG lower bound, deal with abnormally large false alarm */
	if (pFalseAlmCnt->Cnt_all > 10000) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("dm_DIG(): Abnormally false alarm case.\n"));

		if (pDM_DigTable->LargeFAHit != 3)
			pDM_DigTable->LargeFAHit++;
		if (pDM_DigTable->ForbiddenIGI < CurrentIGI) {
			pDM_DigTable->ForbiddenIGI = CurrentIGI;
			pDM_DigTable->LargeFAHit = 1;
		}

		if (pDM_DigTable->LargeFAHit >= 3) {
			if ((pDM_DigTable->ForbiddenIGI+1) > pDM_DigTable->rx_gain_range_max)
				pDM_DigTable->rx_gain_range_min = pDM_DigTable->rx_gain_range_max;
			else
				pDM_DigTable->rx_gain_range_min = (pDM_DigTable->ForbiddenIGI + 1);
			pDM_DigTable->Recover_cnt = 3600; /* 3600=2hr */
		}

	} else {
		/* Recovery mechanism for IGI lower bound */
		if (pDM_DigTable->Recover_cnt != 0) {
			pDM_DigTable->Recover_cnt--;
		} else {
			if (pDM_DigTable->LargeFAHit < 3) {
				if ((pDM_DigTable->ForbiddenIGI-1) < DIG_Dynamic_MIN) { /* DM_DIG_MIN) */
					pDM_DigTable->ForbiddenIGI = DIG_Dynamic_MIN; /* DM_DIG_MIN; */
					pDM_DigTable->rx_gain_range_min = DIG_Dynamic_MIN; /* DM_DIG_MIN; */
					ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Normal Case: At Lower Bound\n"));
				} else {
					pDM_DigTable->ForbiddenIGI--;
					pDM_DigTable->rx_gain_range_min = (pDM_DigTable->ForbiddenIGI + 1);
					ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Normal Case: Approach Lower Bound\n"));
				}
			} else {
				pDM_DigTable->LargeFAHit = 0;
			}
		}
	}
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD,
		     ("odm_DIG(): pDM_DigTable->LargeFAHit=%d\n",
		     pDM_DigTable->LargeFAHit));

	/* 1 Adjust initial gain by false alarm */
	if (pDM_Odm->bLinked) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): DIG AfterLink\n"));
		if (FirstConnect) {
			CurrentIGI = pDM_Odm->RSSI_Min;
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("DIG: First Connect\n"));
		} else {
			if (pFalseAlmCnt->Cnt_all > DM_DIG_FA_TH2)
				CurrentIGI = CurrentIGI + 4;/* pDM_DigTable->CurIGValue = pDM_DigTable->PreIGValue+2; */
			else if (pFalseAlmCnt->Cnt_all > DM_DIG_FA_TH1)
				CurrentIGI = CurrentIGI + 2;/* pDM_DigTable->CurIGValue = pDM_DigTable->PreIGValue+1; */
			else if (pFalseAlmCnt->Cnt_all < DM_DIG_FA_TH0)
				CurrentIGI = CurrentIGI - 2;/* pDM_DigTable->CurIGValue =pDM_DigTable->PreIGValue-1; */
		}
	} else {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): DIG BeforeLink\n"));
		if (FirstDisConnect) {
			CurrentIGI = pDM_DigTable->rx_gain_range_min;
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): First DisConnect\n"));
		} else {
			/* 2012.03.30 LukeLee: enable DIG before link but with very high thresholds */
			if (pFalseAlmCnt->Cnt_all > 10000)
				CurrentIGI = CurrentIGI + 2;/* pDM_DigTable->CurIGValue = pDM_DigTable->PreIGValue+2; */
			else if (pFalseAlmCnt->Cnt_all > 8000)
				CurrentIGI = CurrentIGI + 1;/* pDM_DigTable->CurIGValue = pDM_DigTable->PreIGValue+1; */
			else if (pFalseAlmCnt->Cnt_all < 500)
				CurrentIGI = CurrentIGI - 1;/* pDM_DigTable->CurIGValue =pDM_DigTable->PreIGValue-1; */
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): England DIG\n"));
		}
	}
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): DIG End Adjust IGI\n"));
	/* 1 Check initial gain by upper/lower bound */
	if (CurrentIGI > pDM_DigTable->rx_gain_range_max)
		CurrentIGI = pDM_DigTable->rx_gain_range_max;
	if (CurrentIGI < pDM_DigTable->rx_gain_range_min)
		CurrentIGI = pDM_DigTable->rx_gain_range_min;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD,
		     ("odm_DIG(): rx_gain_range_max=0x%x, rx_gain_range_min=0x%x\n",
		     pDM_DigTable->rx_gain_range_max, pDM_DigTable->rx_gain_range_min));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): TotalFA=%d\n", pFalseAlmCnt->Cnt_all));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): CurIGValue=0x%x\n", CurrentIGI));

	/* 2 High power RSSI threshold */

	ODM_Write_DIG(pDM_Odm, CurrentIGI);/* ODM_Write_DIG(pDM_Odm, pDM_DigTable->CurIGValue); */
	pDM_DigTable->bMediaConnect_0 = pDM_Odm->bLinked;
	pDM_DigTable->DIG_Dynamic_MIN_0 = DIG_Dynamic_MIN;
}