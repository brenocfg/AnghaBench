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
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {struct ath_softc* priv; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_del_ps_key (struct ath_softc*,struct ieee80211_vif*,struct ieee80211_sta*) ; 
 int /*<<< orphan*/  ath_node_detach (struct ath_softc*,struct ieee80211_sta*) ; 

__attribute__((used)) static int ath9k_sta_remove(struct ieee80211_hw *hw,
			    struct ieee80211_vif *vif,
			    struct ieee80211_sta *sta)
{
	struct ath_softc *sc = hw->priv;

	ath9k_del_ps_key(sc, vif, sta);
	ath_node_detach(sc, sta);

	return 0;
}