#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;
typedef  enum HAL_DEF_VARIABLE { ____Placeholder_HAL_DEF_VARIABLE } HAL_DEF_VARIABLE ;

/* Variables and functions */
 int /*<<< orphan*/  SetHalDefVar (struct adapter*,int,void*) ; 
 int /*<<< orphan*/  _SUCCESS ; 

u8 SetHalDefVar8723B(struct adapter *padapter, enum HAL_DEF_VARIABLE variable, void *pval)
{
	u8 bResult;

	bResult = _SUCCESS;

	switch (variable) {
	default:
		bResult = SetHalDefVar(padapter, variable, pval);
		break;
	}

	return bResult;
}