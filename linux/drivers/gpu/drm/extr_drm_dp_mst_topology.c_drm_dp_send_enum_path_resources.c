#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ port_number; int /*<<< orphan*/  avail_payload_bw_number; int /*<<< orphan*/  full_payload_bw_number; } ;
struct TYPE_5__ {TYPE_1__ path_resources; } ;
struct TYPE_6__ {scalar_t__ reply_type; TYPE_2__ u; } ;
struct drm_dp_sideband_msg_tx {TYPE_3__ reply; struct drm_dp_mst_branch* dst; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_dp_mst_port {scalar_t__ port_num; int /*<<< orphan*/  available_pbn; } ;
struct drm_dp_mst_branch {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_SIDEBAND_REPLY_NAK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int build_enum_path_resources (struct drm_dp_sideband_msg_tx*,scalar_t__) ; 
 int drm_dp_mst_wait_tx_reply (struct drm_dp_mst_branch*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  drm_dp_queue_down_tx (struct drm_dp_mst_topology_mgr*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  kfree (struct drm_dp_sideband_msg_tx*) ; 
 struct drm_dp_sideband_msg_tx* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_dp_send_enum_path_resources(struct drm_dp_mst_topology_mgr *mgr,
					   struct drm_dp_mst_branch *mstb,
					   struct drm_dp_mst_port *port)
{
	int len;
	struct drm_dp_sideband_msg_tx *txmsg;
	int ret;

	txmsg = kzalloc(sizeof(*txmsg), GFP_KERNEL);
	if (!txmsg)
		return -ENOMEM;

	txmsg->dst = mstb;
	len = build_enum_path_resources(txmsg, port->port_num);

	drm_dp_queue_down_tx(mgr, txmsg);

	ret = drm_dp_mst_wait_tx_reply(mstb, txmsg);
	if (ret > 0) {
		if (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK) {
			DRM_DEBUG_KMS("enum path resources nak received\n");
		} else {
			if (port->port_num != txmsg->reply.u.path_resources.port_number)
				DRM_ERROR("got incorrect port in response\n");
			DRM_DEBUG_KMS("enum path resources %d: %d %d\n", txmsg->reply.u.path_resources.port_number, txmsg->reply.u.path_resources.full_payload_bw_number,
			       txmsg->reply.u.path_resources.avail_payload_bw_number);
			port->available_pbn = txmsg->reply.u.path_resources.avail_payload_bw_number;
		}
	}

	kfree(txmsg);
	return 0;
}