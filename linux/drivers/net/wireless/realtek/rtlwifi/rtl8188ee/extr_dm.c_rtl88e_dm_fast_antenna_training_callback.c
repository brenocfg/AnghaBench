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
struct timer_list {int dummy; } ;
struct rtl_priv {struct ieee80211_hw* hw; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fast_antenna_training_timer; } ;

/* Variables and functions */
 struct rtl_priv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl88e_dm_fast_ant_training (struct ieee80211_hw*) ; 
 struct rtl_priv* rtlpriv ; 
 TYPE_1__ works ; 

void rtl88e_dm_fast_antenna_training_callback(struct timer_list *t)
{
	struct rtl_priv *rtlpriv =
		from_timer(rtlpriv, t, works.fast_antenna_training_timer);
	struct ieee80211_hw *hw = rtlpriv->hw;

	rtl88e_dm_fast_ant_training(hw);
}