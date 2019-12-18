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
typedef  int /*<<< orphan*/  u32 ;
struct wmi_tdls_peer_update_cmd_arg {int peer_state; int /*<<< orphan*/  addr; int /*<<< orphan*/  vdev_id; } ;
struct wmi_tdls_peer_capab_arg {int is_peer_responder; int /*<<< orphan*/  peer_uapsd_queues; int /*<<< orphan*/  peer_max_sp; } ;
struct wmi_channel_arg {int dummy; } ;
struct ieee80211_sta {int /*<<< orphan*/  tdls_initiator; int /*<<< orphan*/  uapsd_queues; int /*<<< orphan*/  max_sp; int /*<<< orphan*/  addr; } ;
struct ath10k {int /*<<< orphan*/  conf_mutex; } ;
typedef  enum wmi_tdls_peer_state { ____Placeholder_wmi_tdls_peer_state } wmi_tdls_peer_state ;

/* Variables and functions */
 int WMI_TDLS_PEER_STATE_CONNECTED ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ath10k_wmi_tdls_peer_update (struct ath10k*,struct wmi_tdls_peer_update_cmd_arg*,struct wmi_tdls_peer_capab_arg*,struct wmi_channel_arg*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ath10k_mac_tdls_peer_update(struct ath10k *ar, u32 vdev_id,
				       struct ieee80211_sta *sta,
				       enum wmi_tdls_peer_state state)
{
	int ret;
	struct wmi_tdls_peer_update_cmd_arg arg = {};
	struct wmi_tdls_peer_capab_arg cap = {};
	struct wmi_channel_arg chan_arg = {};

	lockdep_assert_held(&ar->conf_mutex);

	arg.vdev_id = vdev_id;
	arg.peer_state = state;
	ether_addr_copy(arg.addr, sta->addr);

	cap.peer_max_sp = sta->max_sp;
	cap.peer_uapsd_queues = sta->uapsd_queues;

	if (state == WMI_TDLS_PEER_STATE_CONNECTED &&
	    !sta->tdls_initiator)
		cap.is_peer_responder = 1;

	ret = ath10k_wmi_tdls_peer_update(ar, &arg, &cap, &chan_arg);
	if (ret) {
		ath10k_warn(ar, "failed to update tdls peer %pM on vdev %i: %i\n",
			    arg.addr, vdev_id, ret);
		return ret;
	}

	return 0;
}