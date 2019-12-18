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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_bss_conf {scalar_t__ assoc; scalar_t__ enable_beacon; } ;
struct ieee80211_vif {scalar_t__ type; struct ieee80211_bss_conf bss_conf; } ;
struct ath9k_htc_priv {int reconfig_beacon; int rearm_ani; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 

__attribute__((used)) static void ath9k_htc_vif_iter(void *data, u8 *mac, struct ieee80211_vif *vif)
{
	struct ath9k_htc_priv *priv = data;
	struct ieee80211_bss_conf *bss_conf = &vif->bss_conf;

	if ((vif->type == NL80211_IFTYPE_AP ||
	     vif->type == NL80211_IFTYPE_MESH_POINT) &&
	    bss_conf->enable_beacon) {
		priv->reconfig_beacon = true;
		priv->rearm_ani = true;
	}

	if (bss_conf->assoc) {
		priv->rearm_ani = true;
		priv->reconfig_beacon = true;
	}
}