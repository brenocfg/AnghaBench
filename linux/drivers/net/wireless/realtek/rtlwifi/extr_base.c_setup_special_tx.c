#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rtl_ps_ctl {int /*<<< orphan*/  last_delaylps_stamp_jiffies; } ;
struct TYPE_10__ {TYPE_4__* btc_ops; } ;
struct TYPE_6__ {int is_special_data; } ;
struct rtl_priv {TYPE_5__ btcoexist; TYPE_3__* cfg; TYPE_1__ ra; struct ieee80211_hw* hw; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* btc_special_packet_notify ) (struct rtl_priv*,int) ;} ;
struct TYPE_8__ {TYPE_2__* ops; } ;
struct TYPE_7__ {scalar_t__ (* get_btc_status ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rtl_lps_leave (struct ieee80211_hw*) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (struct rtl_priv*,int) ; 

__attribute__((used)) static void setup_special_tx(struct rtl_priv *rtlpriv, struct rtl_ps_ctl *ppsc,
			     int type)
{
	struct ieee80211_hw *hw = rtlpriv->hw;

	rtlpriv->ra.is_special_data = true;
	if (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_special_packet_notify(
					rtlpriv, type);
	rtl_lps_leave(hw);
	ppsc->last_delaylps_stamp_jiffies = jiffies;
}