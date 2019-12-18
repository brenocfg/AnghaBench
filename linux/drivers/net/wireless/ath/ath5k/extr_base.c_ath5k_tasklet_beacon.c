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
typedef  scalar_t__ u64 ;
struct ath5k_hw {scalar_t__ opmode; int /*<<< orphan*/  block; int /*<<< orphan*/  nexttbtt; scalar_t__ bintval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_DBG (struct ath5k_hw*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_BEACON ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  TSF_TO_TU (scalar_t__) ; 
 int /*<<< orphan*/  ath5k_beacon_send (struct ath5k_hw*) ; 
 scalar_t__ ath5k_hw_get_tsf64 (struct ath5k_hw*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath5k_tasklet_beacon(unsigned long data)
{
	struct ath5k_hw *ah = (struct ath5k_hw *) data;

	/*
	 * Software beacon alert--time to send a beacon.
	 *
	 * In IBSS mode we use this interrupt just to
	 * keep track of the next TBTT (target beacon
	 * transmission time) in order to detect whether
	 * automatic TSF updates happened.
	 */
	if (ah->opmode == NL80211_IFTYPE_ADHOC) {
		/* XXX: only if VEOL supported */
		u64 tsf = ath5k_hw_get_tsf64(ah);
		ah->nexttbtt += ah->bintval;
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
				"SWBA nexttbtt: %x hw_tu: %x "
				"TSF: %llx\n",
				ah->nexttbtt,
				TSF_TO_TU(tsf),
				(unsigned long long) tsf);
	} else {
		spin_lock(&ah->block);
		ath5k_beacon_send(ah);
		spin_unlock(&ah->block);
	}
}