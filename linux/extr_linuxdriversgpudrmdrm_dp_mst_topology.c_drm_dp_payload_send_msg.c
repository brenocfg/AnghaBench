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
struct TYPE_2__ {int reply_type; } ;
struct drm_dp_sideband_msg_tx {TYPE_1__ reply; struct drm_dp_mst_branch* dst; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_dp_mst_port {int port_num; int num_sdp_streams; int /*<<< orphan*/  parent; } ;
struct drm_dp_mst_branch {int dummy; } ;

/* Variables and functions */
 int DRM_DP_MAX_SDP_STREAMS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int build_allocate_payload (struct drm_dp_sideband_msg_tx*,int,int,int,int,int*) ; 
 struct drm_dp_mst_branch* drm_dp_get_last_connected_port_and_mstb (struct drm_dp_mst_topology_mgr*,int /*<<< orphan*/ ,int*) ; 
 struct drm_dp_mst_branch* drm_dp_get_validated_mstb_ref (struct drm_dp_mst_topology_mgr*,int /*<<< orphan*/ ) ; 
 struct drm_dp_mst_port* drm_dp_get_validated_port_ref (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*) ; 
 int drm_dp_mst_wait_tx_reply (struct drm_dp_mst_branch*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  drm_dp_put_mst_branch_device (struct drm_dp_mst_branch*) ; 
 int /*<<< orphan*/  drm_dp_put_port (struct drm_dp_mst_port*) ; 
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

	port = drm_dp_get_validated_port_ref(mgr, port);
	if (!port)
		return -EINVAL;

	port_num = port->port_num;
	mstb = drm_dp_get_validated_mstb_ref(mgr, port->parent);
	if (!mstb) {
		mstb = drm_dp_get_last_connected_port_and_mstb(mgr, port->parent, &port_num);

		if (!mstb) {
			drm_dp_put_port(port);
			return -EINVAL;
		}
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

	ret = drm_dp_mst_wait_tx_reply(mstb, txmsg);
	if (ret > 0) {
		if (txmsg->reply.reply_type == 1) {
			ret = -EINVAL;
		} else
			ret = 0;
	}
	kfree(txmsg);
fail_put:
	drm_dp_put_mst_branch_device(mstb);
	drm_dp_put_port(port);
	return ret;
}