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
typedef  int u16 ;
struct iwl_mvm_vif {scalar_t__ tsf_id; } ;
struct iwl_mvm_mac_iface_iterator_data {scalar_t__ preferred_tsf; int /*<<< orphan*/  available_tsf_ids; struct ieee80211_vif* vif; } ;
struct TYPE_2__ {int beacon_int; } ;
struct ieee80211_vif {int type; TYPE_1__ bss_conf; } ;

/* Variables and functions */
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_STATION 128 
 scalar_t__ NUM_TSF_IDS ; 
 int /*<<< orphan*/  __clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 struct iwl_mvm_vif* iwl_mvm_vif_from_mac80211 (struct ieee80211_vif*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  test_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_mvm_mac_tsf_id_iter(void *_data, u8 *mac,
				    struct ieee80211_vif *vif)
{
	struct iwl_mvm_mac_iface_iterator_data *data = _data;
	struct iwl_mvm_vif *mvmvif = iwl_mvm_vif_from_mac80211(vif);
	u16 min_bi;

	/* Skip the interface for which we are trying to assign a tsf_id  */
	if (vif == data->vif)
		return;

	/*
	 * The TSF is a hardware/firmware resource, there are 4 and
	 * the driver should assign and free them as needed. However,
	 * there are cases where 2 MACs should share the same TSF ID
	 * for the purpose of clock sync, an optimization to avoid
	 * clock drift causing overlapping TBTTs/DTIMs for a GO and
	 * client in the system.
	 *
	 * The firmware will decide according to the MAC type which
	 * will be the master and slave. Clients that need to sync
	 * with a remote station will be the master, and an AP or GO
	 * will be the slave.
	 *
	 * Depending on the new interface type it can be slaved to
	 * or become the master of an existing interface.
	 */
	switch (data->vif->type) {
	case NL80211_IFTYPE_STATION:
		/*
		 * The new interface is a client, so if the one we're iterating
		 * is an AP, and the beacon interval of the AP is a multiple or
		 * divisor of the beacon interval of the client, the same TSF
		 * should be used to avoid drift between the new client and
		 * existing AP. The existing AP will get drift updates from the
		 * new client context in this case.
		 */
		if (vif->type != NL80211_IFTYPE_AP ||
		    data->preferred_tsf != NUM_TSF_IDS ||
		    !test_bit(mvmvif->tsf_id, data->available_tsf_ids))
			break;

		min_bi = min(data->vif->bss_conf.beacon_int,
			     vif->bss_conf.beacon_int);

		if (!min_bi)
			break;

		if ((data->vif->bss_conf.beacon_int -
		     vif->bss_conf.beacon_int) % min_bi == 0) {
			data->preferred_tsf = mvmvif->tsf_id;
			return;
		}
		break;

	case NL80211_IFTYPE_AP:
		/*
		 * The new interface is AP/GO, so if its beacon interval is a
		 * multiple or a divisor of the beacon interval of an existing
		 * interface, it should get drift updates from an existing
		 * client or use the same TSF as an existing GO. There's no
		 * drift between TSFs internally but if they used different
		 * TSFs then a new client MAC could update one of them and
		 * cause drift that way.
		 */
		if ((vif->type != NL80211_IFTYPE_AP &&
		     vif->type != NL80211_IFTYPE_STATION) ||
		    data->preferred_tsf != NUM_TSF_IDS ||
		    !test_bit(mvmvif->tsf_id, data->available_tsf_ids))
			break;

		min_bi = min(data->vif->bss_conf.beacon_int,
			     vif->bss_conf.beacon_int);

		if (!min_bi)
			break;

		if ((data->vif->bss_conf.beacon_int -
		     vif->bss_conf.beacon_int) % min_bi == 0) {
			data->preferred_tsf = mvmvif->tsf_id;
			return;
		}
		break;
	default:
		/*
		 * For all other interface types there's no need to
		 * take drift into account. Either they're exclusive
		 * like IBSS and monitor, or we don't care much about
		 * their TSF (like P2P Device), but we won't be able
		 * to share the TSF resource.
		 */
		break;
	}

	/*
	 * Unless we exited above, we can't share the TSF resource
	 * that the virtual interface we're iterating over is using
	 * with the new one, so clear the available bit and if this
	 * was the preferred one, reset that as well.
	 */
	__clear_bit(mvmvif->tsf_id, data->available_tsf_ids);

	if (data->preferred_tsf == mvmvif->tsf_id)
		data->preferred_tsf = NUM_TSF_IDS;
}