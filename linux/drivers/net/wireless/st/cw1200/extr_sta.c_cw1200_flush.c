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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct cw1200_common* priv; } ;
struct cw1200_common {int mode; int /*<<< orphan*/  enable_beacon; } ;

/* Variables and functions */
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_MONITOR 128 
 int /*<<< orphan*/  __cw1200_flush (struct cw1200_common*,int) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

void cw1200_flush(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		  u32 queues, bool drop)
{
	struct cw1200_common *priv = hw->priv;

	switch (priv->mode) {
	case NL80211_IFTYPE_MONITOR:
		drop = true;
		break;
	case NL80211_IFTYPE_AP:
		if (!priv->enable_beacon)
			drop = true;
		break;
	}

	if (!__cw1200_flush(priv, drop))
		wsm_unlock_tx(priv);

	return;
}