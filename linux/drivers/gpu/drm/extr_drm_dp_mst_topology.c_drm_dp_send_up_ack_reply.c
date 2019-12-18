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
struct drm_dp_sideband_msg_tx {int seqno; struct drm_dp_mst_branch* dst; } ;
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  qlock; } ;
struct drm_dp_mst_branch {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drm_dp_encode_up_ack_reply (struct drm_dp_sideband_msg_tx*,int) ; 
 int /*<<< orphan*/  kfree (struct drm_dp_sideband_msg_tx*) ; 
 struct drm_dp_sideband_msg_tx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_single_up_tx_qlock (struct drm_dp_mst_topology_mgr*,struct drm_dp_sideband_msg_tx*) ; 

__attribute__((used)) static int drm_dp_send_up_ack_reply(struct drm_dp_mst_topology_mgr *mgr,
				    struct drm_dp_mst_branch *mstb,
				    int req_type, int seqno, bool broadcast)
{
	struct drm_dp_sideband_msg_tx *txmsg;

	txmsg = kzalloc(sizeof(*txmsg), GFP_KERNEL);
	if (!txmsg)
		return -ENOMEM;

	txmsg->dst = mstb;
	txmsg->seqno = seqno;
	drm_dp_encode_up_ack_reply(txmsg, req_type);

	mutex_lock(&mgr->qlock);

	process_single_up_tx_qlock(mgr, txmsg);

	mutex_unlock(&mgr->qlock);

	kfree(txmsg);
	return 0;
}