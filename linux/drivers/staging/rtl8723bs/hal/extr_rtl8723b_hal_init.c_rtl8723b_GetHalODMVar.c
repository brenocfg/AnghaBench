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
struct adapter {int dummy; } ;
typedef  enum HAL_ODM_VARIABLE { ____Placeholder_HAL_ODM_VARIABLE } HAL_ODM_VARIABLE ;

/* Variables and functions */
 int /*<<< orphan*/  GetHalODMVar (struct adapter*,int,void*,void*) ; 

__attribute__((used)) static void rtl8723b_GetHalODMVar(
	struct adapter *Adapter,
	enum HAL_ODM_VARIABLE eVariable,
	void *pValue1,
	void *pValue2
)
{
	GetHalODMVar(Adapter, eVariable, pValue1, pValue2);
}