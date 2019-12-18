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
struct mlme_priv {int /*<<< orphan*/  dynamic_chk_timer; int /*<<< orphan*/  scan_to_timer; int /*<<< orphan*/  assoc_timer; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_join_timeout_handler ; 
 int /*<<< orphan*/  rtw_dynamic_check_timer_handlder ; 
 int /*<<< orphan*/  rtw_scan_timeout_handler ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtw_init_mlme_timer(struct adapter *padapter)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;

	timer_setup(&pmlmepriv->assoc_timer, _rtw_join_timeout_handler, 0);
	timer_setup(&pmlmepriv->scan_to_timer, rtw_scan_timeout_handler, 0);
	timer_setup(&pmlmepriv->dynamic_chk_timer,
		    rtw_dynamic_check_timer_handlder, 0);
}