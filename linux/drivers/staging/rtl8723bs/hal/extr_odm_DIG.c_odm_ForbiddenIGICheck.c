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
typedef  TYPE_1__* pDIG_T ;
struct TYPE_6__ {int Cnt_all; } ;
struct TYPE_5__ {int rx_gain_range_min; int LargeFAHit; int ForbiddenIGI; int rx_gain_range_max; int Recover_cnt; } ;
struct TYPE_7__ {TYPE_2__ FalseAlmCnt; TYPE_1__ DM_DigTable; } ;
typedef  TYPE_2__* Pfalse_ALARM_STATISTICS ;
typedef  TYPE_3__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

u8 odm_ForbiddenIGICheck(void *pDM_VOID, u8 DIG_Dynamic_MIN, u8 CurrentIGI)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	pDIG_T pDM_DigTable = &pDM_Odm->DM_DigTable;
	Pfalse_ALARM_STATISTICS pFalseAlmCnt = &(pDM_Odm->FalseAlmCnt);
	u8 rx_gain_range_min = pDM_DigTable->rx_gain_range_min;

	if (pFalseAlmCnt->Cnt_all > 10000) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Abnormally false alarm case.\n"));

		if (pDM_DigTable->LargeFAHit != 3)
			pDM_DigTable->LargeFAHit++;

		/* if (pDM_DigTable->ForbiddenIGI < pDM_DigTable->CurIGValue) */
		if (pDM_DigTable->ForbiddenIGI < CurrentIGI) {
			pDM_DigTable->ForbiddenIGI = CurrentIGI;
			/* pDM_DigTable->ForbiddenIGI = pDM_DigTable->CurIGValue; */
			pDM_DigTable->LargeFAHit = 1;
		}

		if (pDM_DigTable->LargeFAHit >= 3) {
			if ((pDM_DigTable->ForbiddenIGI + 2) > pDM_DigTable->rx_gain_range_max)
				rx_gain_range_min = pDM_DigTable->rx_gain_range_max;
			else
				rx_gain_range_min = (pDM_DigTable->ForbiddenIGI + 2);
			pDM_DigTable->Recover_cnt = 1800;
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Abnormally false alarm case: Recover_cnt = %d\n", pDM_DigTable->Recover_cnt));
		}
	} else {
		if (pDM_DigTable->Recover_cnt != 0) {
			pDM_DigTable->Recover_cnt--;
			ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Normal Case: Recover_cnt = %d\n", pDM_DigTable->Recover_cnt));
		} else {
			if (pDM_DigTable->LargeFAHit < 3) {
				if ((pDM_DigTable->ForbiddenIGI - 2) < DIG_Dynamic_MIN) { /* DM_DIG_MIN) */
					pDM_DigTable->ForbiddenIGI = DIG_Dynamic_MIN; /* DM_DIG_MIN; */
					rx_gain_range_min = DIG_Dynamic_MIN; /* DM_DIG_MIN; */
					ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Normal Case: At Lower Bound\n"));
				} else {
					pDM_DigTable->ForbiddenIGI -= 2;
					rx_gain_range_min = (pDM_DigTable->ForbiddenIGI + 2);
					ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Normal Case: Approach Lower Bound\n"));
				}
			} else
				pDM_DigTable->LargeFAHit = 0;
		}
	}

	return rx_gain_range_min;

}