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
struct rtl_stats {int recvsignalpower; } ;
struct TYPE_2__ {int recv_signal_power; } ;
struct rtl_priv {TYPE_1__ stats; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl_update_rxsignalstatistics(struct ieee80211_hw *hw,
					  struct rtl_stats *pstatus)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int weighting = 0;

	if (rtlpriv->stats.recv_signal_power == 0)
		rtlpriv->stats.recv_signal_power = pstatus->recvsignalpower;
	if (pstatus->recvsignalpower > rtlpriv->stats.recv_signal_power)
		weighting = 5;
	else if (pstatus->recvsignalpower < rtlpriv->stats.recv_signal_power)
		weighting = (-5);
	rtlpriv->stats.recv_signal_power = (rtlpriv->stats.recv_signal_power *
		5 + pstatus->recvsignalpower + weighting) / 6;
}