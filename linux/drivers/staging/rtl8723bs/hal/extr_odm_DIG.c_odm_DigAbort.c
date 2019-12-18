#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int SupportAbility; int bDMInitialGainEnable; scalar_t__* pbScanInProcess; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int ODM_BB_DIG ; 
 int ODM_BB_FA_CNT ; 
 int /*<<< orphan*/  ODM_COMP_DIG ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

bool odm_DigAbort(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;

	/* SupportAbility */
	if (!(pDM_Odm->SupportAbility & ODM_BB_FA_CNT)) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Return: SupportAbility ODM_BB_FA_CNT is disabled\n"));
		return	true;
	}

	/* SupportAbility */
	if (!(pDM_Odm->SupportAbility & ODM_BB_DIG)) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Return: SupportAbility ODM_BB_DIG is disabled\n"));
		return	true;
	}

	/* ScanInProcess */
	if (*(pDM_Odm->pbScanInProcess)) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Return: In Scan Progress\n"));
		return	true;
	}

	/* add by Neil Chen to avoid PSD is processing */
	if (pDM_Odm->bDMInitialGainEnable == false) {
		ODM_RT_TRACE(pDM_Odm, ODM_COMP_DIG, ODM_DBG_LOUD, ("odm_DIG(): Return: PSD is Processing\n"));
		return	true;
	}

	return	false;
}