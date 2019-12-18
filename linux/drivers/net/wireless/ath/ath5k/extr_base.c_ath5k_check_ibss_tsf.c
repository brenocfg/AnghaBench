#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_rx_status {scalar_t__ mactime; } ;
struct TYPE_3__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  capab_info; } ;
struct TYPE_4__ {TYPE_1__ beacon; } ;
struct ieee80211_mgmt {TYPE_2__ u; } ;
struct ath5k_hw {scalar_t__ nexttbtt; int /*<<< orphan*/  bintval; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH5K_DBG_UNLIMIT (struct ath5k_hw*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ATH5K_DEBUG_BEACON ; 
 scalar_t__ TSF_TO_TU (scalar_t__) ; 
 int WLAN_CAPABILITY_IBSS ; 
 int /*<<< orphan*/  ath5k_beacon_update_timers (struct ath5k_hw*,scalar_t__) ; 
 int /*<<< orphan*/  ath5k_hw_check_beacon_timers (struct ath5k_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath5k_hw_get_tsf64 (struct ath5k_hw*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath5k_check_ibss_tsf(struct ath5k_hw *ah, struct sk_buff *skb,
		     struct ieee80211_rx_status *rxs)
{
	u64 tsf, bc_tstamp;
	u32 hw_tu;
	struct ieee80211_mgmt *mgmt = (struct ieee80211_mgmt *)skb->data;

	if (le16_to_cpu(mgmt->u.beacon.capab_info) & WLAN_CAPABILITY_IBSS) {
		/*
		 * Received an IBSS beacon with the same BSSID. Hardware *must*
		 * have updated the local TSF. We have to work around various
		 * hardware bugs, though...
		 */
		tsf = ath5k_hw_get_tsf64(ah);
		bc_tstamp = le64_to_cpu(mgmt->u.beacon.timestamp);
		hw_tu = TSF_TO_TU(tsf);

		ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
			"beacon %llx mactime %llx (diff %lld) tsf now %llx\n",
			(unsigned long long)bc_tstamp,
			(unsigned long long)rxs->mactime,
			(unsigned long long)(rxs->mactime - bc_tstamp),
			(unsigned long long)tsf);

		/*
		 * Sometimes the HW will give us a wrong tstamp in the rx
		 * status, causing the timestamp extension to go wrong.
		 * (This seems to happen especially with beacon frames bigger
		 * than 78 byte (incl. FCS))
		 * But we know that the receive timestamp must be later than the
		 * timestamp of the beacon since HW must have synced to that.
		 *
		 * NOTE: here we assume mactime to be after the frame was
		 * received, not like mac80211 which defines it at the start.
		 */
		if (bc_tstamp > rxs->mactime) {
			ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
				"fixing mactime from %llx to %llx\n",
				(unsigned long long)rxs->mactime,
				(unsigned long long)tsf);
			rxs->mactime = tsf;
		}

		/*
		 * Local TSF might have moved higher than our beacon timers,
		 * in that case we have to update them to continue sending
		 * beacons. This also takes care of synchronizing beacon sending
		 * times with other stations.
		 */
		if (hw_tu >= ah->nexttbtt)
			ath5k_beacon_update_timers(ah, bc_tstamp);

		/* Check if the beacon timers are still correct, because a TSF
		 * update might have created a window between them - for a
		 * longer description see the comment of this function: */
		if (!ath5k_hw_check_beacon_timers(ah, ah->bintval)) {
			ath5k_beacon_update_timers(ah, bc_tstamp);
			ATH5K_DBG_UNLIMIT(ah, ATH5K_DEBUG_BEACON,
				"fixed beacon timers after beacon receive\n");
		}
	}
}