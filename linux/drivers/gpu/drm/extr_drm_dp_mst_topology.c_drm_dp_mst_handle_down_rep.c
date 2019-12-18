#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  nak_data; int /*<<< orphan*/  reason; } ;
struct TYPE_9__ {TYPE_2__ nak; } ;
struct TYPE_11__ {scalar_t__ reply_type; TYPE_3__ u; struct drm_dp_mst_branch* req_type; } ;
struct drm_dp_sideband_msg_tx {int /*<<< orphan*/  state; TYPE_6__ reply; } ;
struct drm_dp_sideband_msg_rx {int dummy; } ;
struct TYPE_7__ {int seqno; int /*<<< orphan*/ * rad; int /*<<< orphan*/  lct; } ;
struct TYPE_10__ {int /*<<< orphan*/ * msg; TYPE_1__ initial_hdr; scalar_t__ have_eomt; } ;
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  tx_waitq; int /*<<< orphan*/  qlock; TYPE_4__ down_rep_recv; } ;
struct drm_dp_mst_branch {struct drm_dp_sideband_msg_tx** tx_slots; } ;

/* Variables and functions */
 scalar_t__ DP_SIDEBAND_REPLY_NAK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,struct drm_dp_mst_branch*,...) ; 
 int /*<<< orphan*/  DRM_DP_SIDEBAND_TX_RX ; 
 struct drm_dp_mst_branch* drm_dp_get_mst_branch_device (struct drm_dp_mst_topology_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dp_get_one_sb_msg (struct drm_dp_mst_topology_mgr*,int) ; 
 int /*<<< orphan*/  drm_dp_mst_nak_reason_str (int /*<<< orphan*/ ) ; 
 int drm_dp_mst_req_type_str (struct drm_dp_mst_branch*) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_put_mstb (struct drm_dp_mst_branch*) ; 
 int /*<<< orphan*/  drm_dp_sideband_parse_reply (TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int drm_dp_mst_handle_down_rep(struct drm_dp_mst_topology_mgr *mgr)
{
	int ret = 0;

	if (!drm_dp_get_one_sb_msg(mgr, false)) {
		memset(&mgr->down_rep_recv, 0,
		       sizeof(struct drm_dp_sideband_msg_rx));
		return 0;
	}

	if (mgr->down_rep_recv.have_eomt) {
		struct drm_dp_sideband_msg_tx *txmsg;
		struct drm_dp_mst_branch *mstb;
		int slot = -1;
		mstb = drm_dp_get_mst_branch_device(mgr,
						    mgr->down_rep_recv.initial_hdr.lct,
						    mgr->down_rep_recv.initial_hdr.rad);

		if (!mstb) {
			DRM_DEBUG_KMS("Got MST reply from unknown device %d\n", mgr->down_rep_recv.initial_hdr.lct);
			memset(&mgr->down_rep_recv, 0, sizeof(struct drm_dp_sideband_msg_rx));
			return 0;
		}

		/* find the message */
		slot = mgr->down_rep_recv.initial_hdr.seqno;
		mutex_lock(&mgr->qlock);
		txmsg = mstb->tx_slots[slot];
		/* remove from slots */
		mutex_unlock(&mgr->qlock);

		if (!txmsg) {
			DRM_DEBUG_KMS("Got MST reply with no msg %p %d %d %02x %02x\n",
			       mstb,
			       mgr->down_rep_recv.initial_hdr.seqno,
			       mgr->down_rep_recv.initial_hdr.lct,
				      mgr->down_rep_recv.initial_hdr.rad[0],
				      mgr->down_rep_recv.msg[0]);
			drm_dp_mst_topology_put_mstb(mstb);
			memset(&mgr->down_rep_recv, 0, sizeof(struct drm_dp_sideband_msg_rx));
			return 0;
		}

		drm_dp_sideband_parse_reply(&mgr->down_rep_recv, &txmsg->reply);

		if (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK)
			DRM_DEBUG_KMS("Got NAK reply: req 0x%02x (%s), reason 0x%02x (%s), nak data 0x%02x\n",
				      txmsg->reply.req_type,
				      drm_dp_mst_req_type_str(txmsg->reply.req_type),
				      txmsg->reply.u.nak.reason,
				      drm_dp_mst_nak_reason_str(txmsg->reply.u.nak.reason),
				      txmsg->reply.u.nak.nak_data);

		memset(&mgr->down_rep_recv, 0, sizeof(struct drm_dp_sideband_msg_rx));
		drm_dp_mst_topology_put_mstb(mstb);

		mutex_lock(&mgr->qlock);
		txmsg->state = DRM_DP_SIDEBAND_TX_RX;
		mstb->tx_slots[slot] = NULL;
		mutex_unlock(&mgr->qlock);

		wake_up_all(&mgr->tx_waitq);
	}
	return ret;
}