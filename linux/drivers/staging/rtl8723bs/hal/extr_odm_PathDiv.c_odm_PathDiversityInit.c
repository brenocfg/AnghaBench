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
struct TYPE_3__ {int SupportAbility; } ;
typedef  TYPE_1__* PDM_ODM_T ;

/* Variables and functions */
 int ODM_BB_PATH_DIV ; 
 int /*<<< orphan*/  ODM_COMP_PATH_DIV ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RT_TRACE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

void odm_PathDiversityInit(void *pDM_VOID)
{
	PDM_ODM_T pDM_Odm = (PDM_ODM_T)pDM_VOID;

	if (!(pDM_Odm->SupportAbility & ODM_BB_PATH_DIV))
		ODM_RT_TRACE(
			pDM_Odm,
			ODM_COMP_PATH_DIV,
			ODM_DBG_LOUD,
			("Return: Not Support PathDiv\n")
		);
}