#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tolerance_cnt; scalar_t__ NHMCurRxOkcnt; scalar_t__ NHMCurTxOkcnt; scalar_t__ NHMLastRxOkcnt; scalar_t__ NHMLastTxOkcnt; scalar_t__ adaptivity_flag; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */

void odm_NHMBBInit(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;

	pDM_Odm->adaptivity_flag = 0;
	pDM_Odm->tolerance_cnt = 3;
	pDM_Odm->NHMLastTxOkcnt = 0;
	pDM_Odm->NHMLastRxOkcnt = 0;
	pDM_Odm->NHMCurTxOkcnt = 0;
	pDM_Odm->NHMCurRxOkcnt = 0;
}