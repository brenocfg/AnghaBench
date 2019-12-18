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
struct mlme_priv {int dummy; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expire_timeout_chk (struct adapter*) ; 
 int /*<<< orphan*/  linked_status_chk (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_dm_watchdog (struct adapter*) ; 
 int /*<<< orphan*/  traffic_status_watchdog (struct adapter*) ; 

__attribute__((used)) static void dynamic_chk_wk_hdl(struct adapter *padapter, u8 *pbuf, int sz)
{
	struct mlme_priv *pmlmepriv;

	padapter = (struct adapter *)pbuf;
	pmlmepriv = &padapter->mlmepriv;

#ifdef CONFIG_88EU_AP_MODE
	if (check_fwstate(pmlmepriv, WIFI_AP_STATE))
		expire_timeout_chk(padapter);
#endif

	linked_status_chk(padapter);
	traffic_status_watchdog(padapter);

	rtw_hal_dm_watchdog(padapter);
}