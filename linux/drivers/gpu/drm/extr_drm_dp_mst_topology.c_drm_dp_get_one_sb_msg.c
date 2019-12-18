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
struct drm_dp_sideband_msg_rx {int curchunk_len; int curchunk_hdrlen; } ;
struct drm_dp_mst_topology_mgr {int /*<<< orphan*/  aux; int /*<<< orphan*/  max_dpcd_transaction_bytes; struct drm_dp_sideband_msg_rx down_rep_recv; struct drm_dp_sideband_msg_rx up_req_recv; } ;

/* Variables and functions */
 int DP_SIDEBAND_MSG_DOWN_REP_BASE ; 
 int DP_SIDEBAND_MSG_UP_REQ_BASE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int drm_dp_sideband_msg_build (struct drm_dp_sideband_msg_rx*,int /*<<< orphan*/ *,int,int) ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int min3 (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool drm_dp_get_one_sb_msg(struct drm_dp_mst_topology_mgr *mgr, bool up)
{
	int len;
	u8 replyblock[32];
	int replylen, origlen, curreply;
	int ret;
	struct drm_dp_sideband_msg_rx *msg;
	int basereg = up ? DP_SIDEBAND_MSG_UP_REQ_BASE : DP_SIDEBAND_MSG_DOWN_REP_BASE;
	msg = up ? &mgr->up_req_recv : &mgr->down_rep_recv;

	len = min(mgr->max_dpcd_transaction_bytes, 16);
	ret = drm_dp_dpcd_read(mgr->aux, basereg,
			       replyblock, len);
	if (ret != len) {
		DRM_DEBUG_KMS("failed to read DPCD down rep %d %d\n", len, ret);
		return false;
	}
	ret = drm_dp_sideband_msg_build(msg, replyblock, len, true);
	if (!ret) {
		DRM_DEBUG_KMS("sideband msg build failed %d\n", replyblock[0]);
		return false;
	}
	replylen = msg->curchunk_len + msg->curchunk_hdrlen;

	origlen = replylen;
	replylen -= len;
	curreply = len;
	while (replylen > 0) {
		len = min3(replylen, mgr->max_dpcd_transaction_bytes, 16);
		ret = drm_dp_dpcd_read(mgr->aux, basereg + curreply,
				    replyblock, len);
		if (ret != len) {
			DRM_DEBUG_KMS("failed to read a chunk (len %d, ret %d)\n",
				      len, ret);
			return false;
		}

		ret = drm_dp_sideband_msg_build(msg, replyblock, len, false);
		if (!ret) {
			DRM_DEBUG_KMS("failed to build sideband msg\n");
			return false;
		}

		curreply += len;
		replylen -= len;
	}
	return true;
}