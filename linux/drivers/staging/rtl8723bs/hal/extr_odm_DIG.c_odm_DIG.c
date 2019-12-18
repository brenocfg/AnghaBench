#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  TYPE_2__* pDIG_T ;
struct TYPE_10__ {int NumQryBeaconPkt; } ;
struct TYPE_12__ {scalar_t__ Cnt_all; } ;
struct TYPE_11__ {int CurIGValue; int DIG_Dynamic_MIN_0; int bMediaConnect_0; int rx_gain_range_max; int AntDiv_RSSI_max; int rx_gain_range_min; int ForbiddenIGI; int BT30_CurIGI; scalar_t__ LargeFAHit; } ;
struct TYPE_13__ {int adaptivity_flag; int Adaptivity_IGI_upper; int bLinked; int bBtLimitedDig; int RSSI_Min; int SupportAbility; scalar_t__ AntDivType; int IGI_LowerBound; scalar_t__ bBtConnectProcess; scalar_t__ bLinkInProcess; scalar_t__ bBtHsOperation; TYPE_1__ PhyDbgInfo; scalar_t__ bsta_state; int /*<<< orphan*/  bOneEntryOnly; TYPE_3__ FalseAlmCnt; TYPE_2__ DM_DigTable; } ;
typedef  TYPE_3__* Pfalse_ALARM_STATISTICS ;
typedef  TYPE_4__* PDM_ODM_T ;

/* Variables and functions */
 scalar_t__ CG_TRX_HW_ANTDIV ; 
 scalar_t__ CG_TRX_SMART_ANTDIV ; 
 scalar_t__ DM_DIG_FA_TH1 ; 
 int DM_DIG_MAX_AP ; 
 int DM_DIG_MIN_NIC ; 
 int ODM_BB_ADAPTIVITY ; 
 int ODM_BB_ANT_DIV ; 
 int /*<<< orphan*/  ODM_COMP_ANT_DIV ; 
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ODM_Write_DIG (TYPE_4__*,int) ; 
 scalar_t__ S0S1_SW_ANTDIV ; 
 scalar_t__ odm_DigAbort (TYPE_4__*) ; 
 int /*<<< orphan*/  odm_FAThresholdCheck (TYPE_4__*,int,int,scalar_t__,scalar_t__,scalar_t__*) ; 
 int odm_ForbiddenIGICheck (TYPE_4__*,int,int) ; 

void odm_DIG(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;

	/*  Common parameters */
	pDIG_T pDM_DigTable = &pDM_Odm->DM_DigTable;
	Pfalse_ALARM_STATISTICS pFalseAlmCnt = &pDM_Odm->FalseAlmCnt;
	bool FirstConnect, FirstDisConnect;
	u8 DIG_MaxOfMin, DIG_Dynamic_MIN;
	u8 dm_dig_max, dm_dig_min;
	u8 CurrentIGI = pDM_DigTable->CurIGValue;
	u8 offset;
	u32 dm_FA_thres[3];
	u8 Adap_IGI_Upper = 0;
	u32 TxTp = 0, RxTp = 0;
	bool bDFSBand = false;
	bool bPerformance = true, bFirstTpTarget = false, bFirstCoverage = false;

	if (odm_DigAbort(pDM_Odm))
		return;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG() ===========================>\n\n"));

	if (pDM_Odm->adaptivity_flag == true)
		Adap_IGI_Upper = pDM_Odm->Adaptivity_IGI_upper;


	/* 1 Update status */
	DIG_Dynamic_MIN = pDM_DigTable->DIG_Dynamic_MIN_0;
	FirstConnect = (pDM_Odm->bLinked) && (pDM_DigTable->bMediaConnect_0 == false);
	FirstDisConnect = (!pDM_Odm->bLinked) && (pDM_DigTable->bMediaConnect_0 == true);

	/* 1 Boundary Decision */
	/* 2 For WIN\CE */
	dm_dig_max = 0x5A;
	dm_dig_min = DM_DIG_MIN_NIC;
	DIG_MaxOfMin = DM_DIG_MAX_AP;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Absolutely upper bound = 0x%x, lower bound = 0x%x\n", dm_dig_max, dm_dig_min));

	/* 1 Adjust boundary by RSSI */
	if (pDM_Odm->bLinked && bPerformance) {
		/* 2 Modify DIG upper bound */
		/* 4 Modify DIG upper bound for 92E, 8723A\B, 8821 & 8812 BT */
		if (pDM_Odm->bBtLimitedDig == 1) {
			offset = 10;
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Coex. case: Force upper bound to RSSI + %d !!!!!!\n", offset));
		} else
			offset = 15;

		if ((pDM_Odm->RSSI_Min + offset) > dm_dig_max)
			pDM_DigTable->rx_gain_range_max = dm_dig_max;
		else if ((pDM_Odm->RSSI_Min + offset) < dm_dig_min)
			pDM_DigTable->rx_gain_range_max = dm_dig_min;
		else
			pDM_DigTable->rx_gain_range_max = pDM_Odm->RSSI_Min + offset;

		/* 2 Modify DIG lower bound */
		/* if (pDM_Odm->bOneEntryOnly) */
		{
			if (pDM_Odm->RSSI_Min < dm_dig_min)
				DIG_Dynamic_MIN = dm_dig_min;
			else if (pDM_Odm->RSSI_Min > DIG_MaxOfMin)
				DIG_Dynamic_MIN = DIG_MaxOfMin;
			else
				DIG_Dynamic_MIN = pDM_Odm->RSSI_Min;
		}
	} else {
		pDM_DigTable->rx_gain_range_max = dm_dig_max;
		DIG_Dynamic_MIN = dm_dig_min;
	}

	/* 1 Force Lower Bound for AntDiv */
	if (pDM_Odm->bLinked && !pDM_Odm->bOneEntryOnly) {
		if (pDM_Odm->SupportAbility & ODM_BB_ANT_DIV) {
			if (
				pDM_Odm->AntDivType == CG_TRX_HW_ANTDIV ||
				pDM_Odm->AntDivType == CG_TRX_SMART_ANTDIV ||
				pDM_Odm->AntDivType == S0S1_SW_ANTDIV
			) {
				if (pDM_DigTable->AntDiv_RSSI_max > DIG_MaxOfMin)
					DIG_Dynamic_MIN = DIG_MaxOfMin;
				else
					DIG_Dynamic_MIN = (u8) pDM_DigTable->AntDiv_RSSI_max;
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_ANT_DIV,
					ODM_DBG_LOUD,
					(
						"odm_DIG(): Antenna diversity case: Force lower bound to 0x%x !!!!!!\n",
						DIG_Dynamic_MIN
					)
				);
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_ANT_DIV,
					ODM_DBG_LOUD,
					(
						"odm_DIG(): Antenna diversity case: RSSI_max = 0x%x !!!!!!\n",
						pDM_DigTable->AntDiv_RSSI_max
					)
				);
			}
		}
	}
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_DIG,
		ODM_DBG_LOUD,
		(
			"odm_DIG(): Adjust boundary by RSSI Upper bound = 0x%x, Lower bound = 0x%x\n",
			pDM_DigTable->rx_gain_range_max,
			DIG_Dynamic_MIN
		)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_DIG,
		ODM_DBG_LOUD,
		(
			"odm_DIG(): Link status: bLinked = %d, RSSI = %d, bFirstConnect = %d, bFirsrDisConnect = %d\n\n",
			pDM_Odm->bLinked,
			pDM_Odm->RSSI_Min,
			FirstConnect,
			FirstDisConnect
		)
	);

	/* 1 Modify DIG lower bound, deal with abnormal case */
	/* 2 Abnormal false alarm case */
	if (FirstDisConnect) {
		pDM_DigTable->rx_gain_range_min = DIG_Dynamic_MIN;
		pDM_DigTable->ForbiddenIGI = DIG_Dynamic_MIN;
	} else
		pDM_DigTable->rx_gain_range_min =
			odm_ForbiddenIGICheck(pDM_Odm, DIG_Dynamic_MIN, CurrentIGI);

	if (pDM_Odm->bLinked && !FirstConnect) {
		if (
			(pDM_Odm->PhyDbgInfo.NumQryBeaconPkt < 5) &&
			pDM_Odm->bsta_state
		) {
			pDM_DigTable->rx_gain_range_min = dm_dig_min;
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_DIG,
				ODM_DBG_LOUD,
				(
					"odm_DIG(): Abnormal #beacon (%d) case in STA mode: Force lower bound to 0x%x !!!!!!\n\n",
					pDM_Odm->PhyDbgInfo.NumQryBeaconPkt,
					pDM_DigTable->rx_gain_range_min
				)
			);
		}
	}

	/* 2 Abnormal lower bound case */
	if (pDM_DigTable->rx_gain_range_min > pDM_DigTable->rx_gain_range_max) {
		pDM_DigTable->rx_gain_range_min = pDM_DigTable->rx_gain_range_max;
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_DIG,
			ODM_DBG_LOUD,
			(
				"odm_DIG(): Abnormal lower bound case: Force lower bound to 0x%x !!!!!!\n\n",
				pDM_DigTable->rx_gain_range_min
			)
		);
	}


	/* 1 False alarm threshold decision */
	odm_FAThresholdCheck(pDM_Odm, bDFSBand, bPerformance, RxTp, TxTp, dm_FA_thres);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): False alarm threshold = %d, %d, %d\n\n", dm_FA_thres[0], dm_FA_thres[1], dm_FA_thres[2]));

	/* 1 Adjust initial gain by false alarm */
	if (pDM_Odm->bLinked && bPerformance) {
		/* 2 After link */
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_DIG,
			ODM_DBG_LOUD,
			("odm_DIG(): Adjust IGI after link\n")
		);

		if (bFirstTpTarget || (FirstConnect && bPerformance)) {
			pDM_DigTable->LargeFAHit = 0;

			if (pDM_Odm->RSSI_Min < DIG_MaxOfMin) {
				if (CurrentIGI < pDM_Odm->RSSI_Min)
					CurrentIGI = pDM_Odm->RSSI_Min;
			} else {
				if (CurrentIGI < DIG_MaxOfMin)
					CurrentIGI = DIG_MaxOfMin;
			}

			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_DIG,
				ODM_DBG_LOUD,
				(
					"odm_DIG(): First connect case: IGI does on-shot to 0x%x\n",
					CurrentIGI
				)
			);

		} else {
			if (pFalseAlmCnt->Cnt_all > dm_FA_thres[2])
				CurrentIGI = CurrentIGI + 4;
			else if (pFalseAlmCnt->Cnt_all > dm_FA_thres[1])
				CurrentIGI = CurrentIGI + 2;
			else if (pFalseAlmCnt->Cnt_all < dm_FA_thres[0])
				CurrentIGI = CurrentIGI - 2;

			if (
				(pDM_Odm->PhyDbgInfo.NumQryBeaconPkt < 5) &&
				(pFalseAlmCnt->Cnt_all < DM_DIG_FA_TH1) &&
				(pDM_Odm->bsta_state)
			) {
				CurrentIGI = pDM_DigTable->rx_gain_range_min;
				ODM_RT_TRACE(
					pDM_Odm,
					ODM_COMP_DIG,
					ODM_DBG_LOUD,
					(
						"odm_DIG(): Abnormal #beacon (%d) case: IGI does one-shot to 0x%x\n",
						pDM_Odm->PhyDbgInfo.NumQryBeaconPkt,
						CurrentIGI
					)
				);
			}
		}
	} else {
		/* 2 Before link */
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_DIG,
			ODM_DBG_LOUD,
			("odm_DIG(): Adjust IGI before link\n")
		);

		if (FirstDisConnect || bFirstCoverage) {
			CurrentIGI = dm_dig_min;
			ODM_RT_TRACE(
				pDM_Odm,
				ODM_COMP_DIG,
				ODM_DBG_LOUD,
				("odm_DIG(): First disconnect case: IGI does on-shot to lower bound\n")
			);
		} else {
			if (pFalseAlmCnt->Cnt_all > dm_FA_thres[2])
				CurrentIGI = CurrentIGI + 4;
			else if (pFalseAlmCnt->Cnt_all > dm_FA_thres[1])
				CurrentIGI = CurrentIGI + 2;
			else if (pFalseAlmCnt->Cnt_all < dm_FA_thres[0])
				CurrentIGI = CurrentIGI - 2;
		}
	}

	/* 1 Check initial gain by upper/lower bound */
	if (CurrentIGI < pDM_DigTable->rx_gain_range_min)
		CurrentIGI = pDM_DigTable->rx_gain_range_min;

	if (CurrentIGI > pDM_DigTable->rx_gain_range_max)
		CurrentIGI = pDM_DigTable->rx_gain_range_max;

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_DIG,
		ODM_DBG_LOUD,
		(
			"odm_DIG(): CurIGValue = 0x%x, TotalFA = %d\n\n",
			CurrentIGI,
			pFalseAlmCnt->Cnt_all
		)
	);

	/* 1 Force upper bound and lower bound for adaptivity */
	if (
		pDM_Odm->SupportAbility & ODM_BB_ADAPTIVITY &&
		pDM_Odm->adaptivity_flag == true
	) {
		if (CurrentIGI > Adap_IGI_Upper)
			CurrentIGI = Adap_IGI_Upper;

		if (pDM_Odm->IGI_LowerBound != 0) {
			if (CurrentIGI < pDM_Odm->IGI_LowerBound)
				CurrentIGI = pDM_Odm->IGI_LowerBound;
		}
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Adaptivity case: Force upper bound to 0x%x !!!!!!\n", Adap_IGI_Upper));
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Adaptivity case: Force lower bound to 0x%x !!!!!!\n\n", pDM_Odm->IGI_LowerBound));
	}


	/* 1 Update status */
	if (pDM_Odm->bBtHsOperation) {
		if (pDM_Odm->bLinked) {
			if (pDM_DigTable->BT30_CurIGI > (CurrentIGI))
				ODM_Write_DIG(pDM_Odm, CurrentIGI);
			else
				ODM_Write_DIG(pDM_Odm, pDM_DigTable->BT30_CurIGI);

			pDM_DigTable->bMediaConnect_0 = pDM_Odm->bLinked;
			pDM_DigTable->DIG_Dynamic_MIN_0 = DIG_Dynamic_MIN;
		} else {
			if (pDM_Odm->bLinkInProcess)
				ODM_Write_DIG(pDM_Odm, 0x1c);
			else if (pDM_Odm->bBtConnectProcess)
				ODM_Write_DIG(pDM_Odm, 0x28);
			else
				ODM_Write_DIG(pDM_Odm, pDM_DigTable->BT30_CurIGI);/* ODM_Write_DIG(pDM_Odm, pDM_DigTable->CurIGValue); */
		}
	} else { /*  BT is not using */
		ODM_Write_DIG(pDM_Odm, CurrentIGI);/* ODM_Write_DIG(pDM_Odm, pDM_DigTable->CurIGValue); */
		pDM_DigTable->bMediaConnect_0 = pDM_Odm->bLinked;
		pDM_DigTable->DIG_Dynamic_MIN_0 = DIG_Dynamic_MIN;
	}
}