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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int reply_type; } ;
struct drm_dp_sideband_msg_tx {TYPE_1__ reply; struct drm_dp_mst_branch* dst; } ;
struct drm_dp_mst_topology_mgr {int dummy; } ;
struct drm_dp_mst_port {int /*<<< orphan*/  port_num; int /*<<< orphan*/  parent; } ;
struct drm_dp_mst_branch {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int build_dpcd_write (struct drm_dp_sideband_msg_tx*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 struct drm_dp_mst_branch* drm_dp_get_validated_mstb_ref (struct drm_dp_mst_topology_mgr*,int /*<<< orphan*/ ) ; 
 int drm_dp_mst_wait_tx_reply (struct drm_dp_mst_branch*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  drm_dp_put_mst_branch_device (struct drm_dp_mst_branch*) ; 
 int /*<<< orphan*/  drm_dp_queue_down_tx (struct drm_dp_mst_topology_mgr*,struct drm_dp_sideband_msg_tx*) ; 
 int /*<<< orphan*/  kfree (struct drm_dp_sideband_msg_tx*) ; 
 struct drm_dp_sideband_msg_tx* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int drm_dp_send_dpcd_write(struct drm_dp_mst_topology_mgr *mgr,
				  struct drm_dp_mst_port *port,
				  int offset, int size, u8 *bytes)
{
	int len;
	int ret;
	struct drm_dp_sideband_msg_tx *txmsg;
	struct drm_dp_mst_branch *mstb;

	mstb = drm_dp_get_validated_mstb_ref(mgr, port->parent);
	if (!mstb)
		return -EINVAL;

	txmsg = kzalloc(sizeof(*txmsg), GFP_KERNEL);
	if (!txmsg) {
		ret = -ENOMEM;
		goto fail_put;
	}

	len = build_dpcd_write(txmsg, port->port_num, offset, size, bytes);
	txmsg->dst = mstb;

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
	return ret;
}