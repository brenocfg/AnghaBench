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
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct hdcp_port_data {int dummy; } ;
struct TYPE_4__ {struct hdcp_port_data port_data; } ;
struct intel_connector {TYPE_2__ base; TYPE_1__ hdcp; } ;
struct i915_hdcp_comp_master {int /*<<< orphan*/  mei_dev; TYPE_3__* ops; } ;
struct hdcp2_ake_send_cert {int dummy; } ;
struct hdcp2_ake_no_stored_km {int dummy; } ;
struct drm_i915_private {int /*<<< orphan*/  hdcp_comp_mutex; struct i915_hdcp_comp_master* hdcp_master; } ;
struct TYPE_6__ {int (* verify_receiver_cert_prepare_km ) (int /*<<< orphan*/ ,struct hdcp_port_data*,struct hdcp2_ake_send_cert*,int*,struct hdcp2_ake_no_stored_km*,size_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,struct hdcp_port_data*,struct hdcp2_ake_send_cert*,int*,struct hdcp2_ake_no_stored_km*,size_t*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdcp2_verify_rx_cert_prepare_km(struct intel_connector *connector,
				struct hdcp2_ake_send_cert *rx_cert,
				bool *paired,
				struct hdcp2_ake_no_stored_km *ek_pub_km,
				size_t *msg_sz)
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

	ret = comp->ops->verify_receiver_cert_prepare_km(comp->mei_dev, data,
							 rx_cert, paired,
							 ek_pub_km, msg_sz);
	if (ret < 0)
		DRM_DEBUG_KMS("Verify rx_cert failed. %d\n", ret);
	mutex_unlock(&dev_priv->hdcp_comp_mutex);

	return ret;
}