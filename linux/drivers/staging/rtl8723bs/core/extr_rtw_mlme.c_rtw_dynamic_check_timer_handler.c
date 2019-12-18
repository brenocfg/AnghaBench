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
typedef  scalar_t__ u8 ;
struct adapter {int hw_init_completed; int bDriverStopped; int bSurpriseRemoved; int net_closed; } ;
struct TYPE_2__ {int bFwCurrentInPSMode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* adapter_to_pwrctl (struct adapter*) ; 
 int hal_btcoex_IsBtControlLps (struct adapter*) ; 
 int /*<<< orphan*/  hal_btcoex_IsBtDisabled (struct adapter*) ; 
 scalar_t__ is_primary_adapter (struct adapter*) ; 
 int /*<<< orphan*/  linked_status_chk (struct adapter*) ; 
 int /*<<< orphan*/  rtw_auto_scan_handler (struct adapter*) ; 
 int /*<<< orphan*/  rtw_dynamic_chk_wk_cmd (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_dm_watchdog_in_lps (struct adapter*) ; 
 scalar_t__ traffic_status_watchdog (struct adapter*,int) ; 

void rtw_dynamic_check_timer_handler(struct adapter *adapter)
{
	if (!adapter)
		return;

	if (adapter->hw_init_completed == false)
		return;

	if ((adapter->bDriverStopped == true) || (adapter->bSurpriseRemoved == true))
		return;

	if (adapter->net_closed == true)
		return;

	if (is_primary_adapter(adapter))
		DBG_871X("IsBtDisabled =%d, IsBtControlLps =%d\n", hal_btcoex_IsBtDisabled(adapter), hal_btcoex_IsBtControlLps(adapter));

	if ((adapter_to_pwrctl(adapter)->bFwCurrentInPSMode == true)
		&& (hal_btcoex_IsBtControlLps(adapter) == false)
		) {
		u8 bEnterPS;

		linked_status_chk(adapter);

		bEnterPS = traffic_status_watchdog(adapter, 1);
		if (bEnterPS) {
			/* rtw_lps_ctrl_wk_cmd(adapter, LPS_CTRL_ENTER, 1); */
			rtw_hal_dm_watchdog_in_lps(adapter);
		} else {
			/* call rtw_lps_ctrl_wk_cmd(padapter, LPS_CTRL_LEAVE, 1) in traffic_status_watchdog() */
		}

	} else {
		if (is_primary_adapter(adapter)) {
			rtw_dynamic_chk_wk_cmd(adapter);
		}
	}

	/* auto site survey */
	rtw_auto_scan_handler(adapter);
}