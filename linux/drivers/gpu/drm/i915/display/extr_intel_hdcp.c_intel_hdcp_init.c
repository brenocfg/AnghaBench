#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct intel_hdcp_shim {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  streams; } ;
struct intel_hdcp {int hdcp2_supported; int /*<<< orphan*/  cp_irq_queue; int /*<<< orphan*/  prop_work; int /*<<< orphan*/  check_work; int /*<<< orphan*/  mutex; struct intel_hdcp_shim const* shim; TYPE_1__ port_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct intel_connector {TYPE_2__ base; struct intel_hdcp hdcp; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int drm_connector_attach_content_protection_property (TYPE_2__*,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_hdcp2_init (struct intel_connector*,struct intel_hdcp_shim const*) ; 
 int /*<<< orphan*/  intel_hdcp_check_work ; 
 int /*<<< orphan*/  intel_hdcp_prop_work ; 
 scalar_t__ is_hdcp2_supported (struct drm_i915_private*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

int intel_hdcp_init(struct intel_connector *connector,
		    const struct intel_hdcp_shim *shim)
{
	struct drm_i915_private *dev_priv = to_i915(connector->base.dev);
	struct intel_hdcp *hdcp = &connector->hdcp;
	int ret;

	if (!shim)
		return -EINVAL;

	if (is_hdcp2_supported(dev_priv))
		intel_hdcp2_init(connector, shim);

	ret =
	drm_connector_attach_content_protection_property(&connector->base,
							 hdcp->hdcp2_supported);
	if (ret) {
		hdcp->hdcp2_supported = false;
		kfree(hdcp->port_data.streams);
		return ret;
	}

	hdcp->shim = shim;
	mutex_init(&hdcp->mutex);
	INIT_DELAYED_WORK(&hdcp->check_work, intel_hdcp_check_work);
	INIT_WORK(&hdcp->prop_work, intel_hdcp_prop_work);
	init_waitqueue_head(&hdcp->cp_irq_queue);

	return 0;
}