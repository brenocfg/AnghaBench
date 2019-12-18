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
struct timer_list {int dummy; } ;
struct rtl_priv {TYPE_2__* cfg; struct rtl_priv* buddy_priv; struct ieee80211_hw* hw; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dualmac_easyconcurrent_retrytimer; } ;
struct TYPE_5__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dualmac_easy_concurrent ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 struct rtl_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtlpriv ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 TYPE_3__ works ; 

void rtl_easy_concurrent_retrytimer_callback(struct timer_list *t)
{
	struct rtl_priv *rtlpriv =
		from_timer(rtlpriv, t, works.dualmac_easyconcurrent_retrytimer);
	struct ieee80211_hw *hw = rtlpriv->hw;
	struct rtl_priv *buddy_priv = rtlpriv->buddy_priv;

	if (buddy_priv == NULL)
		return;

	rtlpriv->cfg->ops->dualmac_easy_concurrent(hw);
}