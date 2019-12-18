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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ rf_pwrstate; int ps_flag; scalar_t__ bInternalAutoSuspend; } ;
struct adapter {int net_closed; int /*<<< orphan*/  bup; int /*<<< orphan*/  hw_init_completed; TYPE_1__ pwrctrlpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LED_CTL_POWER_OFF ; 
 int /*<<< orphan*/  LeaveAllPowerSaveMode (struct adapter*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  led_control_8188eu (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 scalar_t__ rf_off ; 
 scalar_t__ rf_on ; 
 int /*<<< orphan*/  rtw_disassoc_cmd (struct adapter*,int,int) ; 
 int /*<<< orphan*/  rtw_free_assoc_resources (struct adapter*) ; 
 int /*<<< orphan*/  rtw_free_network_queue (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_indicate_disconnect (struct adapter*) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtw_netif_queue_stopped (struct net_device*) ; 

__attribute__((used)) static int netdev_close(struct net_device *pnetdev)
{
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(pnetdev);

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("+88eu_drv - drv_close\n"));

	if (padapter->pwrctrlpriv.bInternalAutoSuspend) {
		if (padapter->pwrctrlpriv.rf_pwrstate == rf_off)
			padapter->pwrctrlpriv.ps_flag = true;
	}
	padapter->net_closed = true;

	if (padapter->pwrctrlpriv.rf_pwrstate == rf_on) {
		DBG_88E("(2)88eu_drv - drv_close, bup =%d, hw_init_completed =%d\n",
			padapter->bup, padapter->hw_init_completed);

		/* s1. */
		if (pnetdev) {
			if (!rtw_netif_queue_stopped(pnetdev))
				netif_tx_stop_all_queues(pnetdev);
		}

		/* s2. */
		LeaveAllPowerSaveMode(padapter);
		rtw_disassoc_cmd(padapter, 500, false);
		/* s2-2.  indicate disconnect to os */
		rtw_indicate_disconnect(padapter);
		/* s2-3. */
		rtw_free_assoc_resources(padapter);
		/* s2-4. */
		rtw_free_network_queue(padapter, true);
		/*  Close LED */
		led_control_8188eu(padapter, LED_CTL_POWER_OFF);
	}

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("-88eu_drv - drv_close\n"));
	DBG_88E("-88eu_drv - drv_close, bup =%d\n", padapter->bup);
	return 0;
}