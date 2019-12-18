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
struct iwl_mu_group_mgmt_notif {int /*<<< orphan*/  user_position; int /*<<< orphan*/  membership_status; } ;
struct ieee80211_vif {scalar_t__ mu_mimo_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_update_mu_groups (struct ieee80211_vif*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_mu_mimo_iface_iterator(void *_data, u8 *mac,
					   struct ieee80211_vif *vif)
{
	if (vif->mu_mimo_owner) {
		struct iwl_mu_group_mgmt_notif *notif = _data;

		/*
		 * MU-MIMO Group Id action frame is little endian. We treat
		 * the data received from firmware as if it came from the
		 * action frame, so no conversion is needed.
		 */
		ieee80211_update_mu_groups(vif,
					   (u8 *)&notif->membership_status,
					   (u8 *)&notif->user_position);
	}
}