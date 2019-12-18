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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  sent_timestamp; } ;
struct TYPE_4__ {int state; size_t cur_sta_id; TYPE_1__ peer; } ;
struct iwl_mvm {TYPE_2__ tdls_cs; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * fw_id_to_mac_id; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;
typedef  enum iwl_tdls_channel_switch_type { ____Placeholder_iwl_tdls_channel_switch_type } iwl_tdls_channel_switch_type ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct ieee80211_sta*) ; 
 int /*<<< orphan*/  IWL_DEBUG_TDLS (struct iwl_mvm*,char*,int,int,int /*<<< orphan*/  const*,int,int) ; 
 size_t IWL_MVM_INVALID_STA ; 
#define  IWL_MVM_TDLS_SW_ACTIVE 132 
#define  IWL_MVM_TDLS_SW_IDLE 131 
#define  IWL_MVM_TDLS_SW_REQ_RCVD 130 
#define  IWL_MVM_TDLS_SW_REQ_SENT 129 
#define  IWL_MVM_TDLS_SW_RESP_RCVD 128 
 int TDLS_MOVE_CH ; 
 int TDLS_SEND_CHAN_SW_REQ ; 
 int TDLS_SEND_CHAN_SW_RESP_AND_MOVE_CH ; 
 int ether_addr_equal (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct ieee80211_sta* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwl_mvm_tdls_check_action(struct iwl_mvm *mvm,
			  enum iwl_tdls_channel_switch_type type,
			  const u8 *peer, bool peer_initiator, u32 timestamp)
{
	bool same_peer = false;
	int ret = 0;

	/* get the existing peer if it's there */
	if (mvm->tdls_cs.state != IWL_MVM_TDLS_SW_IDLE &&
	    mvm->tdls_cs.cur_sta_id != IWL_MVM_INVALID_STA) {
		struct ieee80211_sta *sta = rcu_dereference_protected(
				mvm->fw_id_to_mac_id[mvm->tdls_cs.cur_sta_id],
				lockdep_is_held(&mvm->mutex));
		if (!IS_ERR_OR_NULL(sta))
			same_peer = ether_addr_equal(peer, sta->addr);
	}

	switch (mvm->tdls_cs.state) {
	case IWL_MVM_TDLS_SW_IDLE:
		/*
		 * might be spurious packet from the peer after the switch is
		 * already done
		 */
		if (type == TDLS_MOVE_CH)
			ret = -EINVAL;
		break;
	case IWL_MVM_TDLS_SW_REQ_SENT:
		/* only allow requests from the same peer */
		if (!same_peer)
			ret = -EBUSY;
		else if (type == TDLS_SEND_CHAN_SW_RESP_AND_MOVE_CH &&
			 !peer_initiator)
			/*
			 * We received a ch-switch request while an outgoing
			 * one is pending. Allow it if the peer is the link
			 * initiator.
			 */
			ret = -EBUSY;
		else if (type == TDLS_SEND_CHAN_SW_REQ)
			/* wait for idle before sending another request */
			ret = -EBUSY;
		else if (timestamp <= mvm->tdls_cs.peer.sent_timestamp)
			/* we got a stale response - ignore it */
			ret = -EINVAL;
		break;
	case IWL_MVM_TDLS_SW_RESP_RCVD:
		/*
		 * we are waiting for the FW to give an "active" notification,
		 * so ignore requests in the meantime
		 */
		ret = -EBUSY;
		break;
	case IWL_MVM_TDLS_SW_REQ_RCVD:
		/* as above, allow the link initiator to proceed */
		if (type == TDLS_SEND_CHAN_SW_REQ) {
			if (!same_peer)
				ret = -EBUSY;
			else if (peer_initiator) /* they are the initiator */
				ret = -EBUSY;
		} else if (type == TDLS_MOVE_CH) {
			ret = -EINVAL;
		}
		break;
	case IWL_MVM_TDLS_SW_ACTIVE:
		/*
		 * the only valid request when active is a request to return
		 * to the base channel by the current off-channel peer
		 */
		if (type != TDLS_MOVE_CH || !same_peer)
			ret = -EBUSY;
		break;
	}

	if (ret)
		IWL_DEBUG_TDLS(mvm,
			       "Invalid TDLS action %d state %d peer %pM same_peer %d initiator %d\n",
			       type, mvm->tdls_cs.state, peer, same_peer,
			       peer_initiator);

	return ret;
}