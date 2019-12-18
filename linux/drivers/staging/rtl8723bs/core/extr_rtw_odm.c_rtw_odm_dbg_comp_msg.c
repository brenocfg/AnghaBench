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
typedef  int u64 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT0 ; 
 int /*<<< orphan*/  DBG_871X_SEL_NL (void*,char*,char,...) ; 
 int /*<<< orphan*/  HW_DEF_ODM_DBG_FLAG ; 
 int RTW_ODM_COMP_MAX ; 
 scalar_t__* odm_comp_str ; 
 int /*<<< orphan*/  rtw_hal_get_def_var (struct adapter*,int /*<<< orphan*/ ,int*) ; 

void rtw_odm_dbg_comp_msg(void *sel, struct adapter *adapter)
{
	u64 dbg_comp;
	int i;

	rtw_hal_get_def_var(adapter, HW_DEF_ODM_DBG_FLAG, &dbg_comp);
	DBG_871X_SEL_NL(sel, "odm.DebugComponents = 0x%016llx\n", dbg_comp);
	for (i = 0; i < RTW_ODM_COMP_MAX; i++) {
		if (odm_comp_str[i])
			DBG_871X_SEL_NL(sel, "%cBIT%-2d %s\n",
					(BIT0 << i) & dbg_comp ? '+' : ' ',
					i, odm_comp_str[i]);
	}
}