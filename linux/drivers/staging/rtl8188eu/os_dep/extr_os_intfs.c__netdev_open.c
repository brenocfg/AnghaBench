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
typedef  scalar_t__ uint ;
struct pwrctrl_priv {int bips_processing; scalar_t__ ps_flag; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dynamic_chk_timer; } ;
struct adapter {int bup; int net_closed; int bDriverStopped; int bSurpriseRemoved; struct pwrctrl_priv pwrctrlpriv; TYPE_1__ mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*,int) ; 
 int /*<<< orphan*/  LED_CTL_NO_LINK ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 scalar_t__ init_hw_mlme_ext (struct adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  led_control_8188eu (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_start_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  rtw_hal_inirp_init (struct adapter*) ; 
 scalar_t__ rtw_hal_init (struct adapter*) ; 
 scalar_t__ rtw_netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtw_netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  rtw_set_pwr_state_check_timer (struct pwrctrl_priv*) ; 
 int rtw_start_drv_threads (struct adapter*) ; 

__attribute__((used)) static int _netdev_open(struct net_device *pnetdev)
{
	uint status;
	int err;
	struct adapter *padapter = (struct adapter *)rtw_netdev_priv(pnetdev);
	struct pwrctrl_priv *pwrctrlpriv = &padapter->pwrctrlpriv;

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("+88eu_drv - dev_open\n"));
	DBG_88E("+88eu_drv - drv_open, bup =%d\n", padapter->bup);

	if (pwrctrlpriv->ps_flag) {
		padapter->net_closed = false;
		goto netdev_open_normal_process;
	}

	if (!padapter->bup) {
		padapter->bDriverStopped = false;
		padapter->bSurpriseRemoved = false;

		status = rtw_hal_init(padapter);
		if (status == _FAIL) {
			RT_TRACE(_module_os_intfs_c_, _drv_err_, ("rtl88eu_hal_init(): Can't init h/w!\n"));
			goto netdev_open_error;
		}

		pr_info("MAC Address = %pM\n", pnetdev->dev_addr);

		err = rtw_start_drv_threads(padapter);
		if (err) {
			pr_info("Initialize driver software resource Failed!\n");
			goto netdev_open_error;
		}

		if (init_hw_mlme_ext(padapter) == _FAIL) {
			pr_info("can't init mlme_ext_priv\n");
			goto netdev_open_error;
		}
		rtw_hal_inirp_init(padapter);

		led_control_8188eu(padapter, LED_CTL_NO_LINK);

		padapter->bup = true;
	}
	padapter->net_closed = false;

	mod_timer(&padapter->mlmepriv.dynamic_chk_timer,
		  jiffies + msecs_to_jiffies(2000));

	padapter->pwrctrlpriv.bips_processing = false;
	rtw_set_pwr_state_check_timer(&padapter->pwrctrlpriv);

	if (!rtw_netif_queue_stopped(pnetdev))
		netif_tx_start_all_queues(pnetdev);
	else
		netif_tx_wake_all_queues(pnetdev);

netdev_open_normal_process:
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("-88eu_drv - dev_open\n"));
	DBG_88E("-88eu_drv - drv_open, bup =%d\n", padapter->bup);
	return 0;

netdev_open_error:
	padapter->bup = false;
	netif_carrier_off(pnetdev);
	netif_tx_stop_all_queues(pnetdev);
	RT_TRACE(_module_os_intfs_c_, _drv_err_, ("-88eu_drv - dev_open, fail!\n"));
	DBG_88E("-88eu_drv - drv_open fail, bup =%d\n", padapter->bup);
	return -1;
}