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
struct ieee80211_bss_conf {int beacon_int; int /*<<< orphan*/  dtim_period; } ;
struct ieee80211_vif {int type; scalar_t__ drv_priv; struct ieee80211_bss_conf bss_conf; } ;
struct ath_common {int dummy; } ;
struct ath_beacon_config {int beacon_interval; int bmiss_timeout; int /*<<< orphan*/  dtim_period; } ;
struct ath9k_htc_vif {int beacon_configured; } ;
struct ath9k_htc_priv {struct ath_beacon_config cur_beacon_conf; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int ATH_DEFAULT_BMISS_LIMIT ; 
 int /*<<< orphan*/  CONFIG ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  ath9k_htc_beacon_config_adhoc (struct ath9k_htc_priv*,struct ath_beacon_config*) ; 
 int /*<<< orphan*/  ath9k_htc_beacon_config_ap (struct ath9k_htc_priv*,struct ath_beacon_config*) ; 
 int /*<<< orphan*/  ath9k_htc_beacon_config_sta (struct ath9k_htc_priv*,struct ath_beacon_config*) ; 
 int /*<<< orphan*/  ath9k_htc_check_beacon_config (struct ath9k_htc_priv*,struct ieee80211_vif*) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*) ; 

void ath9k_htc_beacon_config(struct ath9k_htc_priv *priv,
			     struct ieee80211_vif *vif)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct ath_beacon_config *cur_conf = &priv->cur_beacon_conf;
	struct ieee80211_bss_conf *bss_conf = &vif->bss_conf;
	struct ath9k_htc_vif *avp = (struct ath9k_htc_vif *) vif->drv_priv;

	if (!ath9k_htc_check_beacon_config(priv, vif))
		return;

	cur_conf->beacon_interval = bss_conf->beacon_int;
	if (cur_conf->beacon_interval == 0)
		cur_conf->beacon_interval = 100;

	cur_conf->dtim_period = bss_conf->dtim_period;
	cur_conf->bmiss_timeout =
		ATH_DEFAULT_BMISS_LIMIT * cur_conf->beacon_interval;

	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		ath9k_htc_beacon_config_sta(priv, cur_conf);
		avp->beacon_configured = true;
		break;
	case NL80211_IFTYPE_ADHOC:
		ath9k_htc_beacon_config_adhoc(priv, cur_conf);
		break;
	case NL80211_IFTYPE_MESH_POINT:
	case NL80211_IFTYPE_AP:
		ath9k_htc_beacon_config_ap(priv, cur_conf);
		break;
	default:
		ath_dbg(common, CONFIG, "Unsupported beaconing mode\n");
		return;
	}
}