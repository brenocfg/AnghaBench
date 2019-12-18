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
struct TYPE_2__ {int /*<<< orphan*/  (* GetHalODMVarHandler ) (struct adapter*,int,void*,void*) ;} ;
struct adapter {TYPE_1__ HalFunc; } ;
typedef  enum HAL_ODM_VARIABLE { ____Placeholder_HAL_ODM_VARIABLE } HAL_ODM_VARIABLE ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct adapter*,int,void*,void*) ; 

void rtw_hal_get_odm_var(struct adapter *padapter, enum HAL_ODM_VARIABLE eVariable, void *pValue1, void *pValue2)
{
	if (padapter->HalFunc.GetHalODMVarHandler)
		padapter->HalFunc.GetHalODMVarHandler(padapter, eVariable, pValue1, pValue2);
}