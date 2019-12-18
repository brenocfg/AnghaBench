#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bCurrentTurboEDCA; int bIsCurRDLState; } ;
struct odm_dm_struct {TYPE_1__ DM_EDCA_Table; struct adapter* Adapter; } ;
struct TYPE_4__ {int bIsAnyNonBEPkts; } ;
struct adapter {TYPE_2__ recvpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_EDCA_TURBO ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_EDCA_BE_PARAM ; 
 int /*<<< orphan*/  ODM_EDCA_BK_PARAM ; 
 int /*<<< orphan*/  ODM_EDCA_VI_PARAM ; 
 int /*<<< orphan*/  ODM_EDCA_VO_PARAM ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_read32 (struct adapter*,int /*<<< orphan*/ ) ; 

void ODM_EdcaTurboInit(struct odm_dm_struct *pDM_Odm)
{
	struct adapter *Adapter = pDM_Odm->Adapter;

	pDM_Odm->DM_EDCA_Table.bCurrentTurboEDCA = false;
	pDM_Odm->DM_EDCA_Table.bIsCurRDLState = false;
	Adapter->recvpriv.bIsAnyNonBEPkts = false;

	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD, ("Original VO PARAM: 0x%x\n", usb_read32(Adapter, ODM_EDCA_VO_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD, ("Original VI PARAM: 0x%x\n", usb_read32(Adapter, ODM_EDCA_VI_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD, ("Original BE PARAM: 0x%x\n", usb_read32(Adapter, ODM_EDCA_BE_PARAM)));
	ODM_RT_TRACE(pDM_Odm, ODM_COMP_EDCA_TURBO, ODM_DBG_LOUD, ("Original BK PARAM: 0x%x\n", usb_read32(Adapter, ODM_EDCA_BK_PARAM)));
}