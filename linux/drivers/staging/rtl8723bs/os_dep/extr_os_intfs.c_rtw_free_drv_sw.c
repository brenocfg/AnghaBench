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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/ * old_pnetdev; } ;
struct adapter {TYPE_2__* pbuddy_adapter; TYPE_1__ rereg_nd_name_priv; int /*<<< orphan*/  recvpriv; int /*<<< orphan*/  stapriv; int /*<<< orphan*/  xmitpriv; int /*<<< orphan*/  mlmepriv; int /*<<< orphan*/  evtpriv; int /*<<< orphan*/  cmdpriv; int /*<<< orphan*/  mlmeextpriv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pbuddy_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  _rtw_free_recv_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_free_sta_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_free_xmit_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mlme_ext_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_cmd_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_evt_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_mlme_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_pwrctrl_priv (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_free_data (struct adapter*) ; 

u8 rtw_free_drv_sw(struct adapter *padapter)
{
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("==>rtw_free_drv_sw"));

	free_mlme_ext_priv(&padapter->mlmeextpriv);

	rtw_free_cmd_priv(&padapter->cmdpriv);

	rtw_free_evt_priv(&padapter->evtpriv);

	rtw_free_mlme_priv(&padapter->mlmepriv);

	/* free_io_queue(padapter); */

	_rtw_free_xmit_priv(&padapter->xmitpriv);

	_rtw_free_sta_priv(&padapter->stapriv); /* will free bcmc_stainfo here */

	_rtw_free_recv_priv(&padapter->recvpriv);

	rtw_free_pwrctrl_priv(padapter);

	/* kfree((void *)padapter); */

	rtw_hal_free_data(padapter);

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("<==rtw_free_drv_sw\n"));

	/* free the old_pnetdev */
	if (padapter->rereg_nd_name_priv.old_pnetdev) {
		free_netdev(padapter->rereg_nd_name_priv.old_pnetdev);
		padapter->rereg_nd_name_priv.old_pnetdev = NULL;
	}

	/*  clear pbuddystruct adapter to avoid access wrong pointer. */
	if (padapter->pbuddy_adapter != NULL)
		padapter->pbuddy_adapter->pbuddy_adapter = NULL;

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("-rtw_free_drv_sw\n"));

	return _SUCCESS;
}