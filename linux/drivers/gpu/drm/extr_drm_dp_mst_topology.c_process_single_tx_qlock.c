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
struct drm_dp_sideband_msg_tx {scalar_t__ state; int seqno; int cur_len; int cur_offset; int /*<<< orphan*/ * msg; } ;
struct drm_dp_sideband_msg_hdr {int somt; int eomt; int msg_len; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ DRM_DP_SIDEBAND_TX_QUEUED ; 
 scalar_t__ DRM_DP_SIDEBAND_TX_SENT ; 
 scalar_t__ DRM_DP_SIDEBAND_TX_START_SEND ; 
 int drm_dp_calc_sb_hdr_size (struct drm_dp_sideband_msg_hdr*) ; 
 int /*<<< orphan*/  drm_dp_crc_sideband_chunk_req (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  drm_dp_encode_sideband_msg_hdr (struct drm_dp_sideband_msg_hdr*,int /*<<< orphan*/ *,int*) ; 
 int drm_dp_send_sideband_msg (struct drm_dp_mst_topology_mgr*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct drm_dp_sideband_msg_hdr*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int set_hdr_from_dst_qlock (struct drm_dp_sideband_msg_hdr*,struct drm_dp_sideband_msg_tx*) ; 

__attribute__((used)) static int process_single_tx_qlock(struct drm_dp_mst_topology_mgr *mgr,
				   struct drm_dp_sideband_msg_tx *txmsg,
				   bool up)
{
	u8 chunk[48];
	struct drm_dp_sideband_msg_hdr hdr;
	int len, space, idx, tosend;
	int ret;

	memset(&hdr, 0, sizeof(struct drm_dp_sideband_msg_hdr));

	if (txmsg->state == DRM_DP_SIDEBAND_TX_QUEUED) {
		txmsg->seqno = -1;
		txmsg->state = DRM_DP_SIDEBAND_TX_START_SEND;
	}

	/* make hdr from dst mst - for replies use seqno
	   otherwise assign one */
	ret = set_hdr_from_dst_qlock(&hdr, txmsg);
	if (ret < 0)
		return ret;

	/* amount left to send in this message */
	len = txmsg->cur_len - txmsg->cur_offset;

	/* 48 - sideband msg size - 1 byte for data CRC, x header bytes */
	space = 48 - 1 - drm_dp_calc_sb_hdr_size(&hdr);

	tosend = min(len, space);
	if (len == txmsg->cur_len)
		hdr.somt = 1;
	if (space >= len)
		hdr.eomt = 1;


	hdr.msg_len = tosend + 1;
	drm_dp_encode_sideband_msg_hdr(&hdr, chunk, &idx);
	memcpy(&chunk[idx], &txmsg->msg[txmsg->cur_offset], tosend);
	/* add crc at end */
	drm_dp_crc_sideband_chunk_req(&chunk[idx], tosend);
	idx += tosend + 1;

	ret = drm_dp_send_sideband_msg(mgr, up, chunk, idx);
	if (ret) {
		DRM_DEBUG_KMS("sideband msg failed to send\n");
		return ret;
	}

	txmsg->cur_offset += tosend;
	if (txmsg->cur_offset == txmsg->cur_len) {
		txmsg->state = DRM_DP_SIDEBAND_TX_SENT;
		return 1;
	}
	return 0;
}