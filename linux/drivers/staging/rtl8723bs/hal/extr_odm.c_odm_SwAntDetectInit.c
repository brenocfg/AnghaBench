#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pSWAT_T ;
struct TYPE_4__ {scalar_t__ SWAS_NoLink_State; void* CurAntenna; void* PreAntenna; int /*<<< orphan*/  SWAS_NoLink_BK_Reg92c; } ;
struct TYPE_5__ {int /*<<< orphan*/  Adapter; TYPE_1__ DM_SWAT_Table; } ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 void* MAIN_ANT ; 
 int /*<<< orphan*/  rDPDT_control ; 
 int /*<<< orphan*/  rtw_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void odm_SwAntDetectInit(PDM_ODM_T pDM_Odm)
{
	pSWAT_T pDM_SWAT_Table = &pDM_Odm->DM_SWAT_Table;

	pDM_SWAT_Table->SWAS_NoLink_BK_Reg92c = rtw_read32(pDM_Odm->Adapter, rDPDT_control);
	pDM_SWAT_Table->PreAntenna = MAIN_ANT;
	pDM_SWAT_Table->CurAntenna = MAIN_ANT;
	pDM_SWAT_Table->SWAS_NoLink_State = 0;
}