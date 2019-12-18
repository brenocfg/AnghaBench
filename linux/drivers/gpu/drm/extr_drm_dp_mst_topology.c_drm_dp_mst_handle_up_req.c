#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct drm_dp_sideband_msg_rx {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  available_pbn; int /*<<< orphan*/  port_number; int /*<<< orphan*/  guid; } ;
struct TYPE_11__ {int /*<<< orphan*/  peer_device_type; int /*<<< orphan*/  input_port; int /*<<< orphan*/  message_capability_status; int /*<<< orphan*/  displayport_device_plug_status; int /*<<< orphan*/  legacy_device_plug_status; int /*<<< orphan*/  port_number; int /*<<< orphan*/  guid; } ;
struct TYPE_9__ {TYPE_2__ resource_stat; TYPE_5__ conn_stat; } ;
struct drm_dp_sideband_msg_req_body {scalar_t__ req_type; TYPE_3__ u; } ;
struct TYPE_7__ {int seqno; int /*<<< orphan*/  lct; int /*<<< orphan*/  rad; int /*<<< orphan*/  broadcast; } ;
struct TYPE_10__ {TYPE_1__ initial_hdr; scalar_t__ have_eomt; } ;
struct drm_dp_mst_topology_mgr {TYPE_4__ up_req_recv; int /*<<< orphan*/  mst_primary; int /*<<< orphan*/  dev; } ;
struct drm_dp_mst_branch {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_CONNECTION_STATUS_NOTIFY ; 
 scalar_t__ DP_RESOURCE_STATUS_NOTIFY ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,...) ; 
 struct drm_dp_mst_branch* drm_dp_get_mst_branch_device (struct drm_dp_mst_topology_mgr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_dp_mst_branch* drm_dp_get_mst_branch_device_by_guid (struct drm_dp_mst_topology_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_get_one_sb_msg (struct drm_dp_mst_topology_mgr*,int) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_put_mstb (struct drm_dp_mst_branch*) ; 
 int /*<<< orphan*/  drm_dp_send_up_ack_reply (struct drm_dp_mst_topology_mgr*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  drm_dp_sideband_parse_req (TYPE_4__*,struct drm_dp_sideband_msg_req_body*) ; 
 int /*<<< orphan*/  drm_dp_update_port (struct drm_dp_mst_branch*,TYPE_5__*) ; 
 int /*<<< orphan*/  drm_kms_helper_hotplug_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int drm_dp_mst_handle_up_req(struct drm_dp_mst_topology_mgr *mgr)
{
	int ret = 0;

	if (!drm_dp_get_one_sb_msg(mgr, true)) {
		memset(&mgr->up_req_recv, 0,
		       sizeof(struct drm_dp_sideband_msg_rx));
		return 0;
	}

	if (mgr->up_req_recv.have_eomt) {
		struct drm_dp_sideband_msg_req_body msg;
		struct drm_dp_mst_branch *mstb = NULL;
		bool seqno;

		if (!mgr->up_req_recv.initial_hdr.broadcast) {
			mstb = drm_dp_get_mst_branch_device(mgr,
							    mgr->up_req_recv.initial_hdr.lct,
							    mgr->up_req_recv.initial_hdr.rad);
			if (!mstb) {
				DRM_DEBUG_KMS("Got MST reply from unknown device %d\n", mgr->up_req_recv.initial_hdr.lct);
				memset(&mgr->up_req_recv, 0, sizeof(struct drm_dp_sideband_msg_rx));
				return 0;
			}
		}

		seqno = mgr->up_req_recv.initial_hdr.seqno;
		drm_dp_sideband_parse_req(&mgr->up_req_recv, &msg);

		if (msg.req_type == DP_CONNECTION_STATUS_NOTIFY) {
			drm_dp_send_up_ack_reply(mgr, mgr->mst_primary, msg.req_type, seqno, false);

			if (!mstb)
				mstb = drm_dp_get_mst_branch_device_by_guid(mgr, msg.u.conn_stat.guid);

			if (!mstb) {
				DRM_DEBUG_KMS("Got MST reply from unknown device %d\n", mgr->up_req_recv.initial_hdr.lct);
				memset(&mgr->up_req_recv, 0, sizeof(struct drm_dp_sideband_msg_rx));
				return 0;
			}

			drm_dp_update_port(mstb, &msg.u.conn_stat);

			DRM_DEBUG_KMS("Got CSN: pn: %d ldps:%d ddps: %d mcs: %d ip: %d pdt: %d\n", msg.u.conn_stat.port_number, msg.u.conn_stat.legacy_device_plug_status, msg.u.conn_stat.displayport_device_plug_status, msg.u.conn_stat.message_capability_status, msg.u.conn_stat.input_port, msg.u.conn_stat.peer_device_type);
			drm_kms_helper_hotplug_event(mgr->dev);

		} else if (msg.req_type == DP_RESOURCE_STATUS_NOTIFY) {
			drm_dp_send_up_ack_reply(mgr, mgr->mst_primary, msg.req_type, seqno, false);
			if (!mstb)
				mstb = drm_dp_get_mst_branch_device_by_guid(mgr, msg.u.resource_stat.guid);

			if (!mstb) {
				DRM_DEBUG_KMS("Got MST reply from unknown device %d\n", mgr->up_req_recv.initial_hdr.lct);
				memset(&mgr->up_req_recv, 0, sizeof(struct drm_dp_sideband_msg_rx));
				return 0;
			}

			DRM_DEBUG_KMS("Got RSN: pn: %d avail_pbn %d\n", msg.u.resource_stat.port_number, msg.u.resource_stat.available_pbn);
		}

		if (mstb)
			drm_dp_mst_topology_put_mstb(mstb);

		memset(&mgr->up_req_recv, 0, sizeof(struct drm_dp_sideband_msg_rx));
	}
	return ret;
}