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
typedef  int u8 ;
struct sk_buff {int dummy; } ;
struct rtl_priv {int dummy; } ;
struct ieee80211_tx_rate_control {struct sk_buff* skb; } ;
struct ieee80211_tx_rate {int dummy; } ;
struct TYPE_2__ {struct ieee80211_tx_rate* rates; } ;
struct ieee80211_tx_info {TYPE_1__ control; } ;
struct ieee80211_sta {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int _rtl_rc_get_highest_rix (struct rtl_priv*,struct ieee80211_sta*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  _rtl_rc_rate_set_series (struct rtl_priv*,struct ieee80211_sta*,struct ieee80211_tx_rate*,struct ieee80211_tx_rate_control*,int,int,int,int) ; 
 int /*<<< orphan*/  ieee80211_is_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_get_fc (struct sk_buff*) ; 

__attribute__((used)) static void rtl_get_rate(void *ppriv, struct ieee80211_sta *sta,
			 void *priv_sta,
			 struct ieee80211_tx_rate_control *txrc)
{
	struct rtl_priv *rtlpriv = ppriv;
	struct sk_buff *skb = txrc->skb;
	struct ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	struct ieee80211_tx_rate *rates = tx_info->control.rates;
	__le16 fc = rtl_get_fc(skb);
	u8 try_per_rate, i, rix;
	bool not_data = !ieee80211_is_data(fc);

	rix = _rtl_rc_get_highest_rix(rtlpriv, sta, skb, not_data);
	try_per_rate = 1;
	_rtl_rc_rate_set_series(rtlpriv, sta, &rates[0], txrc,
				try_per_rate, rix, 1, not_data);

	if (!not_data) {
		for (i = 1; i < 4; i++)
			_rtl_rc_rate_set_series(rtlpriv, sta, &rates[i],
						txrc, i, (rix - i), 1,
						not_data);
	}
}