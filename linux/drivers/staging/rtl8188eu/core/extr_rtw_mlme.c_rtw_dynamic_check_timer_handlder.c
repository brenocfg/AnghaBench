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
struct timer_list {int dummy; } ;
struct registry_priv {int wifi_spec; } ;
struct TYPE_3__ {int /*<<< orphan*/  dynamic_chk_timer; } ;
struct adapter {TYPE_1__ mlmepriv; scalar_t__ net_closed; scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; int /*<<< orphan*/  hw_init_completed; struct registry_priv registrypriv; } ;
struct TYPE_4__ {int /*<<< orphan*/  dynamic_chk_timer; } ;

/* Variables and functions */
 struct adapter* adapter ; 
 struct adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 TYPE_2__ mlmepriv ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  rtw_auto_scan_handler (struct adapter*) ; 
 int /*<<< orphan*/  rtw_dynamic_chk_wk_cmd (struct adapter*) ; 

void rtw_dynamic_check_timer_handlder(struct timer_list *t)
{
	struct adapter *adapter = from_timer(adapter, t,
					     mlmepriv.dynamic_chk_timer);
	struct registry_priv *pregistrypriv = &adapter->registrypriv;

	if (!adapter)
		return;
	if (!adapter->hw_init_completed)
		goto exit;
	if ((adapter->bDriverStopped) || (adapter->bSurpriseRemoved))
		goto exit;
	if (adapter->net_closed)
		goto exit;
	rtw_dynamic_chk_wk_cmd(adapter);

	if (pregistrypriv->wifi_spec == 1) {
		/* auto site survey */
		rtw_auto_scan_handler(adapter);
	}
exit:
	mod_timer(&adapter->mlmepriv.dynamic_chk_timer,
		  jiffies + msecs_to_jiffies(2000));
}