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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct hdcp_port_data {int dummy; } ;
struct TYPE_6__ {struct hdcp_port_data port_data; } ;
struct intel_connector {TYPE_1__ base; TYPE_3__ hdcp; } ;
struct i915_hdcp_comp_master {int /*<<< orphan*/  mei_dev; TYPE_2__* ops; } ;
struct hdcp2_rep_send_receiverid_list {int dummy; } ;
struct hdcp2_rep_send_ack {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  hdcp_comp_mutex; struct i915_hdcp_comp_master* hdcp_master; } ;
struct TYPE_5__ {int (* repeater_check_flow_prepare_ack ) (int /*<<< orphan*/ ,struct hdcp_port_data*,struct hdcp2_rep_send_receiverid_list*,struct hdcp2_rep_send_ack*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,struct hdcp_port_data*,struct hdcp2_rep_send_receiverid_list*,struct hdcp2_rep_send_ack*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdcp2_verify_rep_topology_prepare_ack(struct intel_connector *connector,
				      struct hdcp2_rep_send_receiverid_list
								*rep_topology,
				      struct hdcp2_rep_send_ack *rep_send_ack)
{
	struct hdcp_port_data *data = &connector->hdcp.port_data;
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct i915_hdcp_comp_master *comp;
	int ret;

	mutex_lock(&dev_priv->hdcp_comp_mutex);
	comp = dev_priv->hdcp_master;

	if (!comp || !comp->ops) {
		mutex_unlock(&dev_priv->hdcp_comp_mutex);
		return -EINVAL;
	}

	ret = comp->ops->repeater_check_flow_prepare_ack(comp->mei_dev, data,
							 rep_topology,
							 rep_send_ack);
	if (ret < 0)
		DRM_DEBUG_KMS("Verify rep topology failed. %d\n", ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	return ret;
}