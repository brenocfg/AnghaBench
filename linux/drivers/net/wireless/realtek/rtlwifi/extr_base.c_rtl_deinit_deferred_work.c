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
struct TYPE_2__ {int /*<<< orphan*/  c2hcmd_wq; int /*<<< orphan*/  fwevt_wq; int /*<<< orphan*/  ps_rfon_wq; int /*<<< orphan*/  ps_work; int /*<<< orphan*/  ips_nic_off_wq; int /*<<< orphan*/  watchdog_wq; int /*<<< orphan*/  watchdog_timer; } ;
struct rtl_priv {TYPE_1__ works; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

void rtl_deinit_deferred_work(struct ieee80211_hw *hw, bool ips_wq)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	del_timer_sync(&rtlpriv->works.watchdog_timer);

	cancel_delayed_work_sync(&rtlpriv->works.watchdog_wq);
	if (ips_wq)
		cancel_delayed_work(&rtlpriv->works.ips_nic_off_wq);
	else
		cancel_delayed_work_sync(&rtlpriv->works.ips_nic_off_wq);
	cancel_delayed_work_sync(&rtlpriv->works.ps_work);
	cancel_delayed_work_sync(&rtlpriv->works.ps_rfon_wq);
	cancel_delayed_work_sync(&rtlpriv->works.fwevt_wq);
	cancel_delayed_work_sync(&rtlpriv->works.c2hcmd_wq);
}