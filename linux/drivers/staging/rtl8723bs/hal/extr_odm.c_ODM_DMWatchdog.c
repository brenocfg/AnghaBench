#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_16__ ;

/* Type definitions */
typedef  TYPE_2__* pDIG_T ;
struct TYPE_22__ {scalar_t__ NumQryBeaconPkt; } ;
struct TYPE_23__ {int /*<<< orphan*/  CurIGValue; } ;
struct TYPE_24__ {int* pbPowerSaving; TYPE_1__ PhyDbgInfo; TYPE_2__ DM_DigTable; int /*<<< orphan*/  Adapter; int /*<<< orphan*/  RSSI_Min; } ;
struct TYPE_21__ {scalar_t__ pwr_mode; } ;
typedef  TYPE_3__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_CfoTracking (TYPE_3__*) ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ODM_TXPowerTrackingCheck (TYPE_3__*) ; 
 scalar_t__ PS_MODE_ACTIVE ; 
 TYPE_16__* adapter_to_pwrctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_Adaptivity (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_BasicDbgMessage (TYPE_3__*) ; 
 int /*<<< orphan*/  odm_CCKPacketDetectionThresh (TYPE_3__*) ; 
 int /*<<< orphan*/  odm_CommonInfoSelfUpdate (TYPE_3__*) ; 
 int /*<<< orphan*/  odm_DIG (TYPE_3__*) ; 
 int /*<<< orphan*/  odm_DIGbyRSSI_LPS (TYPE_3__*) ; 
 int /*<<< orphan*/  odm_EdcaTurboCheck (TYPE_3__*) ; 
 int /*<<< orphan*/  odm_FalseAlarmCounterStatistics (TYPE_3__*) ; 
 int /*<<< orphan*/  odm_NHMCounterStatistics (TYPE_3__*) ; 
 int /*<<< orphan*/  odm_PathDiversity (TYPE_3__*) ; 
 int /*<<< orphan*/  odm_RSSIMonitorCheck (TYPE_3__*) ; 
 int /*<<< orphan*/  odm_RefreshRateAdaptiveMask (TYPE_3__*) ; 

void ODM_DMWatchdog(PDM_ODM_T pDM_Odm)
{
	odm_CommonInfoSelfUpdate(pDM_Odm);
	odm_BasicDbgMessage(pDM_Odm);
	odm_FalseAlarmCounterStatistics(pDM_Odm);
	odm_NHMCounterStatistics(pDM_Odm);
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): RSSI = 0x%x\n", pDM_Odm->RSSI_Min));

	odm_RSSIMonitorCheck(pDM_Odm);

	/* For CE Platform(SPRD or Tablet) */
	/* 8723A or 8189ES platform */
	/* NeilChen--2012--08--24-- */
	/* Fix Leave LPS issue */
	if ((adapter_to_pwrctl(pDM_Odm->Adapter)->pwr_mode != PS_MODE_ACTIVE) /*  in LPS mode */
		/*  */
		/* (pDM_Odm->SupportICType & (ODM_RTL8723A))|| */
		/* (pDM_Odm->SupportICType & (ODM_RTL8188E) &&(&&(((pDM_Odm->SupportInterface  == ODM_ITRF_SDIO))) */
		/*  */
	) {
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("----Step1: odm_DIG is in LPS mode\n"));
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("---Step2: 8723AS is in LPS mode\n"));
			odm_DIGbyRSSI_LPS(pDM_Odm);
	} else
		odm_DIG(pDM_Odm);

	{
		pDIG_T pDM_DigTable = &pDM_Odm->DM_DigTable;

		odm_Adaptivity(pDM_Odm, pDM_DigTable->CurIGValue);
	}
	odm_CCKPacketDetectionThresh(pDM_Odm);

	if (*(pDM_Odm->pbPowerSaving) == true)
		return;


	odm_RefreshRateAdaptiveMask(pDM_Odm);
	odm_EdcaTurboCheck(pDM_Odm);
	odm_PathDiversity(pDM_Odm);
	ODM_CfoTracking(pDM_Odm);

	ODM_TXPowerTrackingCheck(pDM_Odm);

	/* odm_EdcaTurboCheck(pDM_Odm); */

	/* 2010.05.30 LukeLee: For CE platform, files in IC subfolders may not be included to be compiled, */
	/*  so compile flags must be left here to prevent from compile errors */
	pDM_Odm->PhyDbgInfo.NumQryBeaconPkt = 0;
}