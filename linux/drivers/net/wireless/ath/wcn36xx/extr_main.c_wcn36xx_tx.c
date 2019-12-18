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
struct wcn36xx_sta {int dummy; } ;
struct wcn36xx {int /*<<< orphan*/  hw; } ;
struct sk_buff {int dummy; } ;
struct ieee80211_tx_control {scalar_t__ sta; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ ,struct sk_buff*) ; 
 struct wcn36xx_sta* wcn36xx_sta_to_priv (scalar_t__) ; 
 scalar_t__ wcn36xx_start_tx (struct wcn36xx*,struct wcn36xx_sta*,struct sk_buff*) ; 

__attribute__((used)) static void wcn36xx_tx(struct ieee80211_hw *hw,
		       struct ieee80211_tx_control *control,
		       struct sk_buff *skb)
{
	struct wcn36xx *wcn = hw->priv;
	struct wcn36xx_sta *sta_priv = NULL;

	if (control->sta)
		sta_priv = wcn36xx_sta_to_priv(control->sta);

	if (wcn36xx_start_tx(wcn, sta_priv, skb))
		ieee80211_free_txskb(wcn->hw, skb);
}