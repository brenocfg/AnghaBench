#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {scalar_t__ Cnt_all; } ;
struct TYPE_6__ {int RSSI_Min; TYPE_1__ FalseAlmCnt; } ;
typedef  TYPE_1__* Pfalse_ALARM_STATISTICS ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 scalar_t__ DM_DIG_FA_TH0_LPS ; 
 scalar_t__ DM_DIG_FA_TH1_LPS ; 
 scalar_t__ DM_DIG_FA_TH2_LPS ; 
 int DM_DIG_MAX_NIC ; 
 int DM_DIG_MIN_NIC ; 
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ODM_Write_DIG (TYPE_2__*,int) ; 
 int RSSI_OFFSET_DIG ; 

void odm_DIGbyRSSI_LPS(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	Pfalse_ALARM_STATISTICS pFalseAlmCnt = &pDM_Odm->FalseAlmCnt;

	u8 RSSI_Lower = DM_DIG_MIN_NIC;   /* 0x1E or 0x1C */
	u8 CurrentIGI = pDM_Odm->RSSI_Min;

	CurrentIGI = CurrentIGI+RSSI_OFFSET_DIG;

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_DIG,
		ODM_DBG_LOUD,
		("odm_DIGbyRSSI_LPS() ==>\n")
	);

	/*  Using FW PS mode to make IGI */
	/* Adjust by  FA in LPS MODE */
	if (pFalseAlmCnt->Cnt_all > DM_DIG_FA_TH2_LPS)
		CurrentIGI = CurrentIGI+4;
	else if (pFalseAlmCnt->Cnt_all > DM_DIG_FA_TH1_LPS)
		CurrentIGI = CurrentIGI+2;
	else if (pFalseAlmCnt->Cnt_all < DM_DIG_FA_TH0_LPS)
		CurrentIGI = CurrentIGI-2;


	/* Lower bound checking */

	/* RSSI Lower bound check */
	if ((pDM_Odm->RSSI_Min-10) > DM_DIG_MIN_NIC)
		RSSI_Lower = pDM_Odm->RSSI_Min-10;
	else
		RSSI_Lower = DM_DIG_MIN_NIC;

	/* Upper and Lower Bound checking */
	if (CurrentIGI > DM_DIG_MAX_NIC)
		CurrentIGI = DM_DIG_MAX_NIC;
	else if (CurrentIGI < RSSI_Lower)
		CurrentIGI = RSSI_Lower;


	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_DIG,
		ODM_DBG_LOUD,
		("odm_DIGbyRSSI_LPS(): pFalseAlmCnt->Cnt_all = %d\n", pFalseAlmCnt->Cnt_all)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_DIG,
		ODM_DBG_LOUD,
		("odm_DIGbyRSSI_LPS(): pDM_Odm->RSSI_Min = %d\n", pDM_Odm->RSSI_Min)
	);
	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_DIG,
		ODM_DBG_LOUD,
		("odm_DIGbyRSSI_LPS(): CurrentIGI = 0x%x\n", CurrentIGI)
	);

	ODM_Write_DIG(pDM_Odm, CurrentIGI);
	/* ODM_Write_DIG(pDM_Odm, pDM_DigTable->CurIGValue); */
}