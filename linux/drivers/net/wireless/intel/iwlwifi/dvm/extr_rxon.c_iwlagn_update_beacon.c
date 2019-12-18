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
struct iwl_priv {int /*<<< orphan*/  beacon_skb; int /*<<< orphan*/  hw; int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_beacon_get (int /*<<< orphan*/ ,struct ieee80211_vif*) ; 
 int iwlagn_send_beacon_cmd (struct iwl_priv*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iwlagn_update_beacon(struct iwl_priv *priv,
				struct ieee80211_vif *vif)
{
	lockdep_assert_held(&priv->mutex);

	dev_kfree_skb(priv->beacon_skb);
	priv->beacon_skb = ieee80211_beacon_get(priv->hw, vif);
	if (!priv->beacon_skb)
		return -ENOMEM;
	return iwlagn_send_beacon_cmd(priv);
}