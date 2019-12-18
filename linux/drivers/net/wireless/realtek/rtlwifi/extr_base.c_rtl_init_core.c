#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  iqk_lock; int /*<<< orphan*/  fw_ps_lock; int /*<<< orphan*/  cck_and_rw_pagea_lock; int /*<<< orphan*/  scan_list_lock; int /*<<< orphan*/  c2hcmd_lock; int /*<<< orphan*/  entry_list_lock; int /*<<< orphan*/  waitq_lock; int /*<<< orphan*/  rf_lock; int /*<<< orphan*/  rf_ps_lock; int /*<<< orphan*/  h2c_lock; int /*<<< orphan*/  irq_th_lock; int /*<<< orphan*/  lps_mutex; int /*<<< orphan*/  ips_mutex; int /*<<< orphan*/  conf_mutex; } ;
struct rtl_priv {int /*<<< orphan*/  c2hcmd_queue; TYPE_3__ tx_report; TYPE_2__ scan_list; int /*<<< orphan*/  entry_list; TYPE_1__ locks; } ;
struct rtl_mac {int /*<<< orphan*/  link_state; struct ieee80211_hw* hw; } ;
struct ieee80211_hw {char* rate_control_algorithm; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAC80211_NOLINK ; 
 int /*<<< orphan*/  _rtl_init_deferred_work (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl_init_mac80211 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_reg_notifier ; 
 scalar_t__ rtl_regd_init (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int rtl_init_core(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *rtlmac = rtl_mac(rtl_priv(hw));

	/* <1> init mac80211 */
	_rtl_init_mac80211(hw);
	rtlmac->hw = hw;

	/* <2> rate control register */
	hw->rate_control_algorithm = "rtl_rc";

	/*
	 * <3> init CRDA must come after init
	 * mac80211 hw  in _rtl_init_mac80211.
	 */
	if (rtl_regd_init(hw, rtl_reg_notifier)) {
		pr_err("REGD init failed\n");
		return 1;
	}

	/* <4> locks */
	mutex_init(&rtlpriv->locks.conf_mutex);
	mutex_init(&rtlpriv->locks.ips_mutex);
	mutex_init(&rtlpriv->locks.lps_mutex);
	spin_lock_init(&rtlpriv->locks.irq_th_lock);
	spin_lock_init(&rtlpriv->locks.h2c_lock);
	spin_lock_init(&rtlpriv->locks.rf_ps_lock);
	spin_lock_init(&rtlpriv->locks.rf_lock);
	spin_lock_init(&rtlpriv->locks.waitq_lock);
	spin_lock_init(&rtlpriv->locks.entry_list_lock);
	spin_lock_init(&rtlpriv->locks.c2hcmd_lock);
	spin_lock_init(&rtlpriv->locks.scan_list_lock);
	spin_lock_init(&rtlpriv->locks.cck_and_rw_pagea_lock);
	spin_lock_init(&rtlpriv->locks.fw_ps_lock);
	spin_lock_init(&rtlpriv->locks.iqk_lock);
	/* <5> init list */
	INIT_LIST_HEAD(&rtlpriv->entry_list);
	INIT_LIST_HEAD(&rtlpriv->scan_list.list);
	skb_queue_head_init(&rtlpriv->tx_report.queue);
	skb_queue_head_init(&rtlpriv->c2hcmd_queue);

	rtlmac->link_state = MAC80211_NOLINK;

	/* <6> init deferred work */
	_rtl_init_deferred_work(hw);

	return 0;
}