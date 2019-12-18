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
struct rtl_stats {int* rx_mimo_sig_qual; } ;
struct TYPE_2__ {int* rx_evm_percentage; } ;
struct rtl_priv {TYPE_1__ stats; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int RX_SMOOTH_FACTOR ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static void rtl92d_loop_over_streams(struct ieee80211_hw *hw,
				     struct rtl_stats *pstats)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int stream;

	for (stream = 0; stream < 2; stream++) {
		if (pstats->rx_mimo_sig_qual[stream] != -1) {
			if (rtlpriv->stats.rx_evm_percentage[stream] == 0) {
				rtlpriv->stats.rx_evm_percentage[stream] =
				    pstats->rx_mimo_sig_qual[stream];
			}
			rtlpriv->stats.rx_evm_percentage[stream] =
			    ((rtlpriv->stats.rx_evm_percentage[stream]
			      * (RX_SMOOTH_FACTOR - 1)) +
			     (pstats->rx_mimo_sig_qual[stream] * 1)) /
			    (RX_SMOOTH_FACTOR);
		}
	}
}