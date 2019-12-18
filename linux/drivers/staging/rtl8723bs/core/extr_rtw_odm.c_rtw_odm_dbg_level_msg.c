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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X_SEL_NL (void*,char*,int,...) ; 
 int /*<<< orphan*/  HW_DEF_ODM_DBG_LEVEL ; 
 int RTW_ODM_DBG_LEVEL_NUM ; 
 scalar_t__* odm_dbg_level_str ; 
 int /*<<< orphan*/  rtw_hal_get_def_var (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rtw_odm_dbg_level_msg(void *sel, struct adapter *adapter)
{
	u32 dbg_level;
	int i;

	rtw_hal_get_def_var(adapter, HW_DEF_ODM_DBG_LEVEL, &dbg_level);
	DBG_871X_SEL_NL(sel, "odm.DebugLevel = %u\n", dbg_level);
	for (i = 0; i < RTW_ODM_DBG_LEVEL_NUM; i++) {
		if (odm_dbg_level_str[i])
			DBG_871X_SEL_NL(sel, "%u %s\n",
					i, odm_dbg_level_str[i]);
	}
}