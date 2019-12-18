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
struct ath_hw {scalar_t__ opmode; int slottime; } ;
struct ath9k_tx_queue_info {int tqi_aifs; int tqi_cwmin; scalar_t__ tqi_cwmax; } ;
struct TYPE_2__ {int beaconq; } ;
struct ath9k_htc_priv {int* hwq_map; TYPE_1__ beacon; struct ath_hw* ah; } ;

/* Variables and functions */
 size_t IEEE80211_AC_BE ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  ath9k_hw_common (struct ath_hw*) ; 
 int /*<<< orphan*/  ath9k_hw_get_txq_props (struct ath_hw*,int,struct ath9k_tx_queue_info*) ; 
 int /*<<< orphan*/  ath9k_hw_resettxqueue (struct ath_hw*,int) ; 
 int /*<<< orphan*/  ath9k_hw_set_txq_props (struct ath_hw*,int,struct ath9k_tx_queue_info*) ; 
 int /*<<< orphan*/  ath_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (struct ath9k_tx_queue_info*,int /*<<< orphan*/ ,int) ; 

void ath9k_htc_beaconq_config(struct ath9k_htc_priv *priv)
{
	struct ath_hw *ah = priv->ah;
	struct ath9k_tx_queue_info qi, qi_be;

	memset(&qi, 0, sizeof(struct ath9k_tx_queue_info));
	memset(&qi_be, 0, sizeof(struct ath9k_tx_queue_info));

	ath9k_hw_get_txq_props(ah, priv->beacon.beaconq, &qi);

	if (priv->ah->opmode == NL80211_IFTYPE_AP ||
	    priv->ah->opmode == NL80211_IFTYPE_MESH_POINT) {
		qi.tqi_aifs = 1;
		qi.tqi_cwmin = 0;
		qi.tqi_cwmax = 0;
	} else if (priv->ah->opmode == NL80211_IFTYPE_ADHOC) {
		int qnum = priv->hwq_map[IEEE80211_AC_BE];

		ath9k_hw_get_txq_props(ah, qnum, &qi_be);

		qi.tqi_aifs = qi_be.tqi_aifs;

		/*
		 * For WIFI Beacon Distribution
		 * Long slot time  : 2x cwmin
		 * Short slot time : 4x cwmin
		 */
		if (ah->slottime == 20)
			qi.tqi_cwmin = 2*qi_be.tqi_cwmin;
		else
			qi.tqi_cwmin = 4*qi_be.tqi_cwmin;

		qi.tqi_cwmax = qi_be.tqi_cwmax;

	}

	if (!ath9k_hw_set_txq_props(ah, priv->beacon.beaconq, &qi)) {
		ath_err(ath9k_hw_common(ah),
			"Unable to update beacon queue %u!\n", priv->beacon.beaconq);
	} else {
		ath9k_hw_resettxqueue(ah, priv->beacon.beaconq);
	}
}