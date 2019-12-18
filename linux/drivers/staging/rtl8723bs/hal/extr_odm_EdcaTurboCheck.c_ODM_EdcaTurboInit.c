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
struct TYPE_6__ {int bIsAnyNonBEPkts; } ;
struct adapter {TYPE_2__ recvpriv; } ;
struct TYPE_5__ {int bCurrentTurboEDCA; int bIsCurRDLState; } ;
struct TYPE_7__ {struct adapter* Adapter; TYPE_1__ DM_EDCA_Table; } ;
typedef  TYPE_3__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_EDCA_TURBO ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_EDCA_BE_PARAM ; 
 int /*<<< orphan*/  ODM_EDCA_BK_PARAM ; 
 int /*<<< orphan*/  ODM_EDCA_VI_PARAM ; 
 int /*<<< orphan*/  ODM_EDCA_VO_PARAM ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rtw_read32 (struct adapter*,int /*<<< orphan*/ ) ; 

void ODM_EdcaTurboInit(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	struct adapter *Adapter = pDM_Odm->Adapter;

	pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = false;
	pDM_Odm->DM_EDCA_Table.bIsCurRDLState = false;
	Adapter->recvpriv.bIsAnyNonBEPkts = false;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("Original VO PARAM: 0x%x\n",
		      rtw_read32(pDM_Odm->Adapter, ODM_EDCA_VO_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("Original VI PARAM: 0x%x\n",
		      rtw_read32(pDM_Odm->Adapter, ODM_EDCA_VI_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("Original BE PARAM: 0x%x\n",
		      rtw_read32(pDM_Odm->Adapter, ODM_EDCA_BE_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD,
		     ("Original BK PARAM: 0x%x\n",
		      rtw_read32(pDM_Odm->Adapter, ODM_EDCA_BK_PARAM)));
}