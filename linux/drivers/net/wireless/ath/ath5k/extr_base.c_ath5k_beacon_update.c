#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ieee80211_vif {scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath5k_vif {TYPE_1__* bbuf; } ;
struct ath5k_hw {int dummy; } ;
struct TYPE_3__ {struct sk_buff* skb; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 int ath5k_beacon_setup (struct ath5k_hw*,TYPE_1__*) ; 
 int /*<<< orphan*/  ath5k_txbuf_free_skb (struct ath5k_hw*,TYPE_1__*) ; 
 struct sk_buff* ieee80211_beacon_get (struct ieee80211_hw*,struct ieee80211_vif*) ; 

int
ath5k_beacon_update(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	int ret;
	struct ath5k_hw *ah = hw->priv;
	struct ath5k_vif *avf;
	struct sk_buff *skb;

	if (WARN_ON(!vif)) {
		ret = -EINVAL;
		goto out;
	}

	skb = ieee80211_beacon_get(hw, vif);

	if (!skb) {
		ret = -ENOMEM;
		goto out;
	}

	avf = (void *)vif->drv_priv;
	ath5k_txbuf_free_skb(ah, avf->bbuf);
	avf->bbuf->skb = skb;
	ret = ath5k_beacon_setup(ah, avf->bbuf);
out:
	return ret;
}