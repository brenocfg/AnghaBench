#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_4__ {struct adapter* padapter; } ;
struct TYPE_3__ {struct adapter* padapter; } ;
struct adapter {TYPE_2__ stapriv; int /*<<< orphan*/  recvpriv; int /*<<< orphan*/  xmitpriv; TYPE_1__ cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_88E (char*) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 scalar_t__ _rtw_init_recv_priv (int /*<<< orphan*/ *,struct adapter*) ; 
 scalar_t__ _rtw_init_sta_priv (TYPE_2__*) ; 
 scalar_t__ _rtw_init_xmit_priv (int /*<<< orphan*/ *,struct adapter*) ; 
 scalar_t__ init_mlme_ext_priv (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_dm_init (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_sreset_init (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_sw_led_init (struct adapter*) ; 
 int /*<<< orphan*/  rtw_init_bcmc_stainfo (struct adapter*) ; 
 scalar_t__ rtw_init_cmd_priv (TYPE_1__*) ; 
 scalar_t__ rtw_init_default_value (struct adapter*) ; 
 scalar_t__ rtw_init_mlme_priv (struct adapter*) ; 
 int /*<<< orphan*/  rtw_init_pwrctrl_priv (struct adapter*) ; 

u8 rtw_init_drv_sw(struct adapter *padapter)
{
	u8 ret8 = _SUCCESS;

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("+rtw_init_drv_sw\n"));

	if ((rtw_init_cmd_priv(&padapter->cmdpriv)) == _FAIL) {
		RT_TRACE(_module_os_intfs_c_, _drv_err_, ("\n Can't init cmd_priv\n"));
		ret8 = _FAIL;
		goto exit;
	}

	padapter->cmdpriv.padapter = padapter;

	if (rtw_init_mlme_priv(padapter) == _FAIL) {
		RT_TRACE(_module_os_intfs_c_, _drv_err_, ("\n Can't init mlme_priv\n"));
		ret8 = _FAIL;
		goto exit;
	}

	if (init_mlme_ext_priv(padapter) == _FAIL) {
		RT_TRACE(_module_os_intfs_c_, _drv_err_, ("\n Can't init mlme_ext_priv\n"));
		ret8 = _FAIL;
		goto exit;
	}

	if (_rtw_init_xmit_priv(&padapter->xmitpriv, padapter) == _FAIL) {
		DBG_88E("Can't _rtw_init_xmit_priv\n");
		ret8 = _FAIL;
		goto exit;
	}

	if (_rtw_init_recv_priv(&padapter->recvpriv, padapter) == _FAIL) {
		DBG_88E("Can't _rtw_init_recv_priv\n");
		ret8 = _FAIL;
		goto exit;
	}

	if (_rtw_init_sta_priv(&padapter->stapriv) == _FAIL) {
		DBG_88E("Can't _rtw_init_sta_priv\n");
		ret8 = _FAIL;
		goto exit;
	}

	padapter->stapriv.padapter = padapter;

	rtw_init_bcmc_stainfo(padapter);

	rtw_init_pwrctrl_priv(padapter);

	ret8 = rtw_init_default_value(padapter);

	rtw_hal_dm_init(padapter);
	rtw_hal_sw_led_init(padapter);

	rtw_hal_sreset_init(padapter);

exit:
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("-rtw_init_drv_sw\n"));

	return ret8;
}