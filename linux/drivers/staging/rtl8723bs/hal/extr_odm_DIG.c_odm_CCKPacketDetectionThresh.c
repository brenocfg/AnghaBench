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
struct TYPE_5__ {int Cnt_Cck_fail; } ;
struct TYPE_6__ {int SupportAbility; int RSSI_Min; scalar_t__ bLinked; scalar_t__ ExtLNA; TYPE_1__ FalseAlmCnt; } ;
typedef  TYPE_1__* Pfalse_ALARM_STATISTICS ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 int ODM_BB_CCK_PD ; 
 int ODM_BB_FA_CNT ; 
 int /*<<< orphan*/  ODM_COMP_CCK_PD ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ODM_Write_CCK_CCA_Thres (TYPE_2__*,int) ; 

void odm_CCKPacketDetectionThresh(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	Pfalse_ALARM_STATISTICS FalseAlmCnt = &(pDM_Odm->FalseAlmCnt);
	u8 CurCCK_CCAThres;


	if (
		!(pDM_Odm->SupportAbility & ODM_BB_CCK_PD) ||
		!(pDM_Odm->SupportAbility & ODM_BB_FA_CNT)
	) {
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_CCK_PD,
			ODM_DBG_LOUD,
			("odm_CCKPacketDetectionThresh()  return ==========\n")
		);
		return;
	}

	if (pDM_Odm->ExtLNA)
		return;

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_CCK_PD,
		ODM_DBG_LOUD,
		("odm_CCKPacketDetectionThresh()  ==========>\n")
	);

	if (pDM_Odm->bLinked) {
		if (pDM_Odm->RSSI_Min > 25)
			CurCCK_CCAThres = 0xcd;
		else if ((pDM_Odm->RSSI_Min <= 25) && (pDM_Odm->RSSI_Min > 10))
			CurCCK_CCAThres = 0x83;
		else {
			if (FalseAlmCnt->Cnt_Cck_fail > 1000)
				CurCCK_CCAThres = 0x83;
			else
				CurCCK_CCAThres = 0x40;
		}
	} else {
		if (FalseAlmCnt->Cnt_Cck_fail > 1000)
			CurCCK_CCAThres = 0x83;
		else
			CurCCK_CCAThres = 0x40;
	}

	ODM_Write_CCK_CCA_Thres(pDM_Odm, CurCCK_CCAThres);

	ODM_RT_TRACE(
		pDM_Odm,
		ODM_COMP_CCK_PD,
		ODM_DBG_LOUD,
		(
			"odm_CCKPacketDetectionThresh()  CurCCK_CCAThres = 0x%x\n",
			CurCCK_CCAThres
		)
	);
}