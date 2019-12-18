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
struct TYPE_2__ {scalar_t__ reply_type; } ;
struct drm_dp_sideband_msg_tx {TYPE_1__ reply; int /*<<< orphan*/  dst; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_dp_mst_port {int /*<<< orphan*/  parent; int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 scalar_t__ DP_SIDEBAND_REPLY_NAK ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int build_power_updown_phy (struct drm_dp_sideband_msg_tx*,int /*<<< orphan*/ ,int) ; 
 struct drm_dp_mst_port* drm_dp_mst_topology_get_port_validated (struct drm_dp_mst_topology_mgr*,struct drm_dp_mst_port*) ; 
 int /*<<< orphan*/  drm_dp_mst_topology_put_port (struct drm_dp_mst_port*) ; 
 int drm_dp_mst_wait_tx_reply (int /*<<< orphan*/ ,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  drm_dp_queue_down_tx (struct drm_dp_mst_topology_mgr*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  kfree (struct drm_dp_sideband_msg_tx*) ; 
 struct drm_dp_sideband_msg_tx* kzalloc (int,int /*<<< orphan*/ ) ; 

int drm_dp_send_power_updown_phy(struct drm_dp_mst_topology_mgr *mgr,
				 struct drm_dp_mst_port *port, bool power_up)
{
	struct drm_dp_sideband_msg_tx *txmsg;
	int len, ret;

	port = drm_dp_mst_topology_get_port_validated(mgr, port);
	if (!port)
		return -EINVAL;

	txmsg = kzalloc(sizeof(*txmsg), GFP_KERNEL);
	if (!txmsg) {
		drm_dp_mst_topology_put_port(port);
		return -ENOMEM;
	}

	txmsg->dst = port->parent;
	len = build_power_updown_phy(txmsg, port->port_num, power_up);
	drm_dp_queue_down_tx(mgr, txmsg);

	ret = drm_dp_mst_wait_tx_reply(port->parent, txmsg);
	if (ret > 0) {
		if (txmsg->reply.reply_type == DP_SIDEBAND_REPLY_NAK)
			ret = -EINVAL;
		else
			ret = 0;
	}
	kfree(txmsg);
	drm_dp_mst_topology_put_port(port);

	return ret;
}