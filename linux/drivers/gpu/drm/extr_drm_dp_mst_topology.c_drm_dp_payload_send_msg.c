#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {scalar_t__ reply_type; } ;
struct drm_dp_sideband_msg_tx {TYPE_1__ reply; struct drm_dp_mst_branch* dst; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_dp_mst_port {int port_num; int num_sdp_streams; int /*<<< orphan*/  parent; } ;
struct drm_dp_mst_branch {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_SIDEBAND_REPLY_NAK ; 
 int DRM_DP_MAX_SDP_STREAMS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int build_allocate_payload (struct drm_dp_sideband_msg_tx*,int,int,int,int,int*) ; 
 struct drm_dp_mst_branch* drm_dp_get_last_connected_port_and_mstb (struct drm_dp_mst_topology_mgr*,int /*<<< orphan*/ ,int*) ; 
 struct drm_dp_mst_branch* drm_dp_mst_topology_get_mstb_validated (struct drm_dp_mst_topology_mgr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_put_mstb (struct drm_dp_mst_branch*) ; 
 int drm_dp_mst_wait_tx_reply (struct drm_dp_mst_branch*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  drm_dp_queue_down_tx (struct drm_dp_mst_topology_mgr*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  kfree (struct drm_dp_sideband_msg_tx*) ; 
 struct drm_dp_sideband_msg_tx* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_dp_payload_send_msg(struct drm_dp_mst_topology_mgr *mgr,
				   struct drm_dp_mst_port *port,
				   int id,
				   int pbn)
{
	struct drm_dp_sideband_msg_tx *txmsg;
	struct drm_dp_mst_branch *mstb;
	int len, ret, port_num;
	u8 sinks[DRM_DP_MAX_SDP_STREAMS];
	int i;

	port_num = port->port_num;
	mstb = drm_dp_mst_topology_get_mstb_validated(mgr, port->parent);
	if (!mstb) {
		mstb = drm_dp_get_last_connected_port_and_mstb(mgr,
							       port->parent,
							       &port_num);

		if (!mstb)
			return -EINVAL;
	}

	txmsg = kzalloc(sizeof(*txmsg), GFP_KERNEL);
	if (!txmsg) {
		ret = -ENOMEM;
		goto fail_put;
	}

	for (i = 0; i < port->num_sdp_streams; i++)
		sinks[i] = i;

	txmsg->dst = mstb;
	len = build_allocate_payload(txmsg, port_num,
				     id,
				     pbn, port->num_sdp_streams, sinks);

	drm_dp_queue_down_tx(mgr, txmsg);

	/*
	 * FIXME: there is a small chance that between getting the last
	 * connected mstb and sending the payload message, the last connected
	 * mstb could also be removed from the topology. In the future, this
	 * needs to be fixed by restarting the
	 * drm_dp_get_last_connected_port_and_mstb() search in the event of a
	 * timeout if the topology is still connected to the system.
	 */
	ret = drm_dp_mst_wait_tx_reply(mstb, txmsg);
	if (ret > 0) {
		if (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK)
			ret = -EINVAL;
		else
			ret = 0;
	}
	kfree(txmsg);
fail_put:
	drm_dp_mst_topology_put_mstb(mstb);
	return ret;
}