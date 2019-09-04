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
struct drm_dp_sideband_msg_tx {scalar_t__ state; size_t seqno; int /*<<< orphan*/  next; } ;
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  qlock; int /*<<< orphan*/  tx_waitq; } ;
struct drm_dp_mst_branch {int /*<<< orphan*/ ** tx_slots; struct drm_dp_mst_topology_mgr* mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,struct drm_dp_sideband_msg_tx*,scalar_t__,size_t) ; 
 scalar_t__ DRM_DP_SIDEBAND_TX_QUEUED ; 
 scalar_t__ DRM_DP_SIDEBAND_TX_SENT ; 
 scalar_t__ DRM_DP_SIDEBAND_TX_START_SEND ; 
 scalar_t__ DRM_DP_SIDEBAND_TX_TIMEOUT ; 
 int EIO ; 
 int HZ ; 
 int /*<<< orphan*/  check_txmsg_state (struct drm_dp_mst_topology_mgr*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int drm_dp_mst_wait_tx_reply(struct drm_dp_mst_branch *mstb,
				    struct drm_dp_sideband_msg_tx *txmsg)
{
	struct drm_dp_mst_topology_mgr *mgr = mstb->mgr;
	int ret;

	ret = wait_event_timeout(mgr->tx_waitq,
				 check_txmsg_state(mgr, txmsg),
				 (4 * HZ));
	mutex_lock(&mstb->mgr->qlock);
	if (ret > 0) {
		if (txmsg->state == DRM_DP_SIDEBAND_TX_TIMEOUT) {
			ret = -EIO;
			goto out;
		}
	} else {
		DRM_DEBUG_KMS("timedout msg send %p %d %d\n", txmsg, txmsg->state, txmsg->seqno);

		/* dump some state */
		ret = -EIO;

		/* remove from q */
		if (txmsg->state == DRM_DP_SIDEBAND_TX_QUEUED ||
		    txmsg->state == DRM_DP_SIDEBAND_TX_START_SEND) {
			list_del(&txmsg->next);
		}

		if (txmsg->state == DRM_DP_SIDEBAND_TX_START_SEND ||
		    txmsg->state == DRM_DP_SIDEBAND_TX_SENT) {
			mstb->tx_slots[txmsg->seqno] = NULL;
		}
	}
out:
	mutex_unlock(&mgr->qlock);

	return ret;
}