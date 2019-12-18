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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct cfg80211_chan_def {int dummy; } ;
struct ath9k_htc_priv {struct ieee80211_vif* csa_vif; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (struct ieee80211_vif*) ; 

__attribute__((used)) static void ath9k_htc_channel_switch_beacon(struct ieee80211_hw *hw,
					    struct ieee80211_vif *vif,
					    struct cfg80211_chan_def *chandef)
{
	struct ath9k_htc_priv *priv = hw->priv;

	/* mac80211 does not support CSA in multi-if cases (yet) */
	if (WARN_ON(priv->csa_vif))
		return;

	priv->csa_vif = vif;
}