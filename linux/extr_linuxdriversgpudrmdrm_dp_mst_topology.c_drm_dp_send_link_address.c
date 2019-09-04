#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nports; TYPE_5__* ports; int /*<<< orphan*/  guid; } ;
struct TYPE_7__ {TYPE_1__ link_addr; } ;
struct TYPE_8__ {int reply_type; TYPE_2__ u; } ;
struct drm_dp_sideband_msg_tx {TYPE_3__ reply; struct drm_dp_mst_branch* dst; } ;
struct drm_dp_mst_topology_mgr {TYPE_4__* cbs; int /*<<< orphan*/  dev; } ;
struct drm_dp_mst_branch {int link_address_sent; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_sdp_stream_sinks; int /*<<< orphan*/  num_sdp_streams; int /*<<< orphan*/  legacy_device_plug_status; int /*<<< orphan*/  ddps; int /*<<< orphan*/  mcs; int /*<<< orphan*/  dpcd_revision; int /*<<< orphan*/  port_number; int /*<<< orphan*/  peer_device_type; int /*<<< orphan*/  input_port; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* hotplug ) (struct drm_dp_mst_topology_mgr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int build_link_address (struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  drm_dp_add_port (struct drm_dp_mst_branch*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  drm_dp_check_mstb_guid (struct drm_dp_mst_branch*,int /*<<< orphan*/ ) ; 
 int drm_dp_mst_wait_tx_reply (struct drm_dp_mst_branch*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  drm_dp_queue_down_tx (struct drm_dp_mst_topology_mgr*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  kfree (struct drm_dp_sideband_msg_tx*) ; 
 struct drm_dp_sideband_msg_tx* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct drm_dp_mst_topology_mgr*) ; 

__attribute__((used)) static void drm_dp_send_link_address(struct drm_dp_mst_topology_mgr *mgr,
				     struct drm_dp_mst_branch *mstb)
{
	int len;
	struct drm_dp_sideband_msg_tx *txmsg;
	int ret;

	txmsg = kzalloc(sizeof(*txmsg), GFP_KERNEL);
	if (!txmsg)
		return;

	txmsg->dst = mstb;
	len = build_link_address(txmsg);

	mstb->link_address_sent = true;
	drm_dp_queue_down_tx(mgr, txmsg);

	ret = drm_dp_mst_wait_tx_reply(mstb, txmsg);
	if (ret > 0) {
		int i;

		if (txmsg->reply.reply_type == 1)
			DRM_DEBUG_KMS("link address nak received\n");
		else {
			DRM_DEBUG_KMS("link address reply: %d\n", txmsg->reply.u.link_addr.nports);
			for (i = 0; i < txmsg->reply.u.link_addr.nports; i++) {
				DRM_DEBUG_KMS("port %d: input %d, pdt: %d, pn: %d, dpcd_rev: %02x, mcs: %d, ddps: %d, ldps %d, sdp %d/%d\n", i,
				       txmsg->reply.u.link_addr.ports[i].input_port,
				       txmsg->reply.u.link_addr.ports[i].peer_device_type,
				       txmsg->reply.u.link_addr.ports[i].port_number,
				       txmsg->reply.u.link_addr.ports[i].dpcd_revision,
				       txmsg->reply.u.link_addr.ports[i].mcs,
				       txmsg->reply.u.link_addr.ports[i].ddps,
				       txmsg->reply.u.link_addr.ports[i].legacy_device_plug_status,
				       txmsg->reply.u.link_addr.ports[i].num_sdp_streams,
				       txmsg->reply.u.link_addr.ports[i].num_sdp_stream_sinks);
			}

			drm_dp_check_mstb_guid(mstb, txmsg->reply.u.link_addr.guid);

			for (i = 0; i < txmsg->reply.u.link_addr.nports; i++) {
				drm_dp_add_port(mstb, mgr->dev, &txmsg->reply.u.link_addr.ports[i]);
			}
			(*mgr->cbs->hotplug)(mgr);
		}
	} else {
		mstb->link_address_sent = false;
		DRM_DEBUG_KMS("link address failed %d\n", ret);
	}

	kfree(txmsg);
}