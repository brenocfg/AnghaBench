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
struct adapter {int /*<<< orphan*/  hw_init_mutex; int /*<<< orphan*/  recvpriv; int /*<<< orphan*/  stapriv; int /*<<< orphan*/  xmitpriv; int /*<<< orphan*/  mlmepriv; int /*<<< orphan*/  mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_os_intfs_c_ ; 
 int /*<<< orphan*/  _rtw_free_recv_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_free_sta_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_free_xmit_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_mlme_ext_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_free_mlme_priv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_hal_free_data (struct adapter*) ; 

u8 rtw_free_drv_sw(struct adapter *padapter)
{
	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("==>rtw_free_drv_sw"));

	free_mlme_ext_priv(&padapter->mlmeextpriv);

	rtw_free_mlme_priv(&padapter->mlmepriv);
	_rtw_free_xmit_priv(&padapter->xmitpriv);

	/* will free bcmc_stainfo here */
	_rtw_free_sta_priv(&padapter->stapriv);

	_rtw_free_recv_priv(&padapter->recvpriv);

	rtw_hal_free_data(padapter);

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("<== rtw_free_drv_sw\n"));

	mutex_destroy(&padapter->hw_init_mutex);

	RT_TRACE(_module_os_intfs_c_, _drv_info_, ("-rtw_free_drv_sw\n"));

	return _SUCCESS;
}