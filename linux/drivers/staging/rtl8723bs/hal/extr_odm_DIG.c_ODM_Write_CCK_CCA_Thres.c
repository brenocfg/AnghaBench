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
typedef  scalar_t__ u8 ;
typedef  TYPE_1__* pDIG_T ;
struct TYPE_4__ {scalar_t__ CurCCK_CCAThres; scalar_t__ PreCCK_CCAThres; } ;
struct TYPE_5__ {int /*<<< orphan*/  Adapter; TYPE_1__ DM_DigTable; } ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */
 int /*<<< orphan*/  CCK_CCA ; 
 int /*<<< orphan*/  ODM_REG (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  rtw_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

void ODM_Write_CCK_CCA_Thres(void *pDM_VOID, u8 CurCCK_CCAThres)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;
	pDIG_T pDM_DigTable = &pDM_Odm->DM_DigTable;

	/* modify by Guo.Mingzhi 2012-01-03 */
	if (pDM_DigTable->CurCCK_CCAThres != CurCCK_CCAThres)
		rtw_write8(pDM_Odm->Adapter, ODM_REG(CCK_CCA, pDM_Odm), CurCCK_CCAThres);

	pDM_DigTable->PreCCK_CCAThres = pDM_DigTable->CurCCK_CCAThres;
	pDM_DigTable->CurCCK_CCAThres = CurCCK_CCAThres;
}