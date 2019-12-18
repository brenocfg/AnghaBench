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
struct mlme_priv {int dummy; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  _linked_info_dump (struct adapter*) ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expire_timeout_chk (struct adapter*) ; 
 int /*<<< orphan*/  hal_btcoex_Handler (struct adapter*) ; 
 scalar_t__ is_primary_adapter (struct adapter*) ; 
 int /*<<< orphan*/  linked_status_chk (struct adapter*) ; 
 int /*<<< orphan*/  rtw_hal_dm_watchdog (struct adapter*) ; 
 int /*<<< orphan*/  rtw_ps_processor (struct adapter*) ; 
 int /*<<< orphan*/  traffic_status_watchdog (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dynamic_chk_wk_hdl(struct adapter *padapter)
{
	struct mlme_priv *pmlmepriv;
	pmlmepriv = &(padapter->mlmepriv);

	if (check_fwstate(pmlmepriv, WIFI_AP_STATE) == true) {
		expire_timeout_chk(padapter);
	}

	/* for debug purpose */
	_linked_info_dump(padapter);


	/* if (check_fwstate(pmlmepriv, _FW_UNDER_LINKING|_FW_UNDER_SURVEY) ==false) */
	{
		linked_status_chk(padapter);
		traffic_status_watchdog(padapter, 0);
	}

	rtw_hal_dm_watchdog(padapter);

	/* check_hw_pbc(padapter, pdrvextra_cmd->pbuf, pdrvextra_cmd->type); */

	/*  */
	/*  BT-Coexist */
	/*  */
	hal_btcoex_Handler(padapter);


	/* always call rtw_ps_processor() at last one. */
	if (is_primary_adapter(padapter))
		rtw_ps_processor(padapter);
}