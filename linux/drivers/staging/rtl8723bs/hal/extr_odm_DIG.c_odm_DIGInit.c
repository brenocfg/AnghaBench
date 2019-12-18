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
typedef  scalar_t__ u8 ;
typedef  TYPE_1__* pDIG_T ;
struct TYPE_5__ {int bStopDIG; int bPSDInProgress; int PreCCK_CCAThres; int CurCCK_CCAThres; int bMediaConnect_0; int bMediaConnect_1; int BT30_CurIGI; void* rx_gain_range_min; int /*<<< orphan*/  rx_gain_range_max; void* DIG_Dynamic_MIN_1; void* DIG_Dynamic_MIN_0; scalar_t__ Recover_cnt; scalar_t__ LargeFAHit; void* ForbiddenIGI; int /*<<< orphan*/  BackoffVal_range_min; int /*<<< orphan*/  BackoffVal_range_max; int /*<<< orphan*/  BackoffVal; int /*<<< orphan*/  FAHighThresh; int /*<<< orphan*/  FALowThresh; int /*<<< orphan*/  RssiHighThresh; int /*<<< orphan*/  RssiLowThresh; scalar_t__ CurIGValue; } ;
struct TYPE_6__ {int bDMInitialGainEnable; int /*<<< orphan*/  Adapter; TYPE_1__ DM_DigTable; } ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  DM_DIG_BACKOFF_DEFAULT ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_MAX ; 
 int /*<<< orphan*/  DM_DIG_BACKOFF_MIN ; 
 int /*<<< orphan*/  DM_DIG_MAX_NIC ; 
 void* DM_DIG_MIN_NIC ; 
 int /*<<< orphan*/  DM_DIG_THRESH_HIGH ; 
 int /*<<< orphan*/  DM_DIG_THRESH_LOW ; 
 int /*<<< orphan*/  DMfalseALARM_THRESH_HIGH ; 
 int /*<<< orphan*/  DMfalseALARM_THRESH_LOW ; 
 int /*<<< orphan*/  IGI ; 
 int /*<<< orphan*/  IGI_A ; 
 int /*<<< orphan*/  ODM_BIT (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ODM_REG (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ PHY_QueryBBReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void odm_DIGInit(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	pDIG_T pDM_DigTable = &pDM_Odm->DM_DigTable;

	pDM_DigTable->bStopDIG = false;
	pDM_DigTable->bPSDInProgress = false;
	pDM_DigTable->CurIGValue = (u8) PHY_QueryBBReg(pDM_Odm->Adapter, ODM_REG(IGI_A, pDM_Odm), ODM_BIT(IGI, pDM_Odm));
	pDM_DigTable->RssiLowThresh	= DM_DIG_THRESH_LOW;
	pDM_DigTable->RssiHighThresh	= DM_DIG_THRESH_HIGH;
	pDM_DigTable->FALowThresh	= DMfalseALARM_THRESH_LOW;
	pDM_DigTable->FAHighThresh	= DMfalseALARM_THRESH_HIGH;
	pDM_DigTable->BackoffVal = DM_DIG_BACKOFF_DEFAULT;
	pDM_DigTable->BackoffVal_range_max = DM_DIG_BACKOFF_MAX;
	pDM_DigTable->BackoffVal_range_min = DM_DIG_BACKOFF_MIN;
	pDM_DigTable->PreCCK_CCAThres = 0xFF;
	pDM_DigTable->CurCCK_CCAThres = 0x83;
	pDM_DigTable->ForbiddenIGI = DM_DIG_MIN_NIC;
	pDM_DigTable->LargeFAHit = 0;
	pDM_DigTable->Recover_cnt = 0;
	pDM_DigTable->bMediaConnect_0 = false;
	pDM_DigTable->bMediaConnect_1 = false;

	/* To Initialize pDM_Odm->bDMInitialGainEnable == false to avoid DIG error */
	pDM_Odm->bDMInitialGainEnable = true;

	pDM_DigTable->DIG_Dynamic_MIN_0 = DM_DIG_MIN_NIC;
	pDM_DigTable->DIG_Dynamic_MIN_1 = DM_DIG_MIN_NIC;

	/* To Initi BT30 IGI */
	pDM_DigTable->BT30_CurIGI = 0x32;

	pDM_DigTable->rx_gain_range_max = DM_DIG_MAX_NIC;
	pDM_DigTable->rx_gain_range_min = DM_DIG_MIN_NIC;

}