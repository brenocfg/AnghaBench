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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  sta_id; } ;
struct il_station_priv {TYPE_1__ common; int /*<<< orphan*/  pending_frames; } ;
struct il_priv {int /*<<< orphan*/  mutex; } ;
struct ieee80211_vif {scalar_t__ type; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; scalar_t__ drv_priv; } ;
struct ieee80211_hw {struct il_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IL_ERR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IL_INVALID_STATION ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_rs_rate_init (struct il_priv*,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int il_add_station_common (struct il_priv*,int /*<<< orphan*/ ,int,struct ieee80211_sta*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int
il4965_mac_sta_add(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		   struct ieee80211_sta *sta)
{
	struct il_priv *il = hw->priv;
	struct il_station_priv *sta_priv = (void *)sta->drv_priv;
	bool is_ap = vif->type == NL80211_IFTYPE_STATION;
	int ret;
	u8 sta_id;

	D_INFO("received request to add station %pM\n", sta->addr);
	mutex_lock(&il->mutex);
	D_INFO("proceeding to add station %pM\n", sta->addr);
	sta_priv->common.sta_id = IL_INVALID_STATION;

	atomic_set(&sta_priv->pending_frames, 0);

	ret =
	    il_add_station_common(il, sta->addr, is_ap, sta, &sta_id);
	if (ret) {
		IL_ERR("Unable to add station %pM (%d)\n", sta->addr, ret);
		/* Should we return success if return code is EEXIST ? */
		mutex_unlock(&il->mutex);
		return ret;
	}

	sta_priv->common.sta_id = sta_id;

	/* Initialize rate scaling */
	D_INFO("Initializing rate scaling for station %pM\n", sta->addr);
	il4965_rs_rate_init(il, sta, sta_id);
	mutex_unlock(&il->mutex);

	return 0;
}