#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  multicast_rsc; } ;
struct TYPE_7__ {int /*<<< orphan*/  multicast_rsc; } ;
union iwl_all_tsc_rsc {TYPE_4__ tkip; TYPE_3__ aes; } ;
struct iwl_wowlan_status {TYPE_2__* gtk; } ;
struct iwl_mvm {int dummy; } ;
struct ieee80211_key_conf {int cipher; } ;
struct TYPE_5__ {union iwl_all_tsc_rsc all_tsc_rsc; } ;
struct TYPE_6__ {TYPE_1__ rsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
#define  WLAN_CIPHER_SUITE_CCMP 129 
#define  WLAN_CIPHER_SUITE_TKIP 128 
 int /*<<< orphan*/  iwl_mvm_set_aes_rx_seq (struct iwl_mvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ieee80211_key_conf*) ; 
 int /*<<< orphan*/  iwl_mvm_set_tkip_rx_seq (int /*<<< orphan*/ ,struct ieee80211_key_conf*) ; 

__attribute__((used)) static void iwl_mvm_set_key_rx_seq(struct iwl_mvm *mvm,
				   struct ieee80211_key_conf *key,
				   struct iwl_wowlan_status *status)
{
	union iwl_all_tsc_rsc *rsc = &status->gtk[0].rsc.all_tsc_rsc;

	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_CCMP:
		iwl_mvm_set_aes_rx_seq(mvm, rsc->aes.multicast_rsc, NULL, key);
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		iwl_mvm_set_tkip_rx_seq(rsc->tkip.multicast_rsc, key);
		break;
	default:
		WARN_ON(1);
	}
}