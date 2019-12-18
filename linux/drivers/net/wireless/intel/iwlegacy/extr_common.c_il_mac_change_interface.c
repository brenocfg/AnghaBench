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
struct il_priv {int iw_mode; int /*<<< orphan*/  mutex; int /*<<< orphan*/  vif; } ;
struct ieee80211_vif {int type; int p2p; int /*<<< orphan*/  addr; } ;
struct ieee80211_hw {struct il_priv* priv; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  D_MAC80211 (char*,int,...) ; 
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  il_is_ready_rf (struct il_priv*) ; 
 int /*<<< orphan*/  il_teardown_interface (struct il_priv*,struct ieee80211_vif*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
il_mac_change_interface(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			enum nl80211_iftype newtype, bool newp2p)
{
	struct il_priv *il = hw->priv;
	int err;

	mutex_lock(&il->mutex);
	D_MAC80211("enter: type %d, addr %pM newtype %d newp2p %d\n",
		    vif->type, vif->addr, newtype, newp2p);

	if (newp2p) {
		err = -EOPNOTSUPP;
		goto out;
	}

	if (!il->vif || !il_is_ready_rf(il)) {
		/*
		 * Huh? But wait ... this can maybe happen when
		 * we're in the middle of a firmware restart!
		 */
		err = -EBUSY;
		goto out;
	}

	/* success */
	vif->type = newtype;
	vif->p2p = false;
	il->iw_mode = newtype;
	il_teardown_interface(il, vif);
	err = 0;

out:
	D_MAC80211("leave err %d\n", err);
	mutex_unlock(&il->mutex);

	return err;
}