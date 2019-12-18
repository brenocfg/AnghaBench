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
struct intel_hdcp {scalar_t__ value; int /*<<< orphan*/  mutex; int /*<<< orphan*/  prop_work; TYPE_3__* shim; int /*<<< orphan*/  hdcp_encrypted; } ;
struct TYPE_7__ {int port; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_4__ base; int /*<<< orphan*/  name; TYPE_1__* dev; } ;
struct intel_connector {TYPE_5__ base; struct intel_hdcp hdcp; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_8__ {scalar_t__ (* check_link ) (struct intel_digital_port*) ;} ;
struct TYPE_6__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,...) ; 
 void* DRM_MODE_CONTENT_PROTECTION_DESIRED ; 
 scalar_t__ DRM_MODE_CONTENT_PROTECTION_ENABLED ; 
 scalar_t__ DRM_MODE_CONTENT_PROTECTION_UNDESIRED ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_HDCP_STATUS (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int _intel_hdcp_disable (struct intel_connector*) ; 
 int _intel_hdcp_enable (struct intel_connector*) ; 
 struct intel_digital_port* conn_to_dig_port (struct intel_connector*) ; 
 int /*<<< orphan*/  intel_hdcp_in_use (struct intel_connector*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct intel_digital_port*) ; 

__attribute__((used)) static int intel_hdcp_check_link(struct intel_connector *connector)
{
	struct intel_hdcp *hdcp = &connector->hdcp;
	struct drm_i915_private *dev_priv = connector->base.dev->dev_private;
	struct intel_digital_port *intel_dig_port = conn_to_dig_port(connector);
	enum port port = intel_dig_port->base.port;
	int ret = 0;

	mutex_lock(&hdcp->mutex);

	/* Check_link valid only when HDCP1.4 is enabled */
	if (hdcp->value != DRM_MODE_CONTENT_PROTECTION_ENABLED ||
	    !hdcp->hdcp_encrypted) {
		ret = -EINVAL;
		goto out;
	}

	if (WARN_ON(!intel_hdcp_in_use(connector))) {
		DRM_ERROR("%s:%d HDCP link stopped encryption,%x\n",
			  connector->base.name, connector->base.base.id,
			  I915_READ(PORT_HDCP_STATUS(port)));
		ret = -ENXIO;
		hdcp->value = DRM_MODE_CONTENT_PROTECTION_DESIRED;
		schedule_work(&hdcp->prop_work);
		goto out;
	}

	if (hdcp->shim->check_link(intel_dig_port)) {
		if (hdcp->value != DRM_MODE_CONTENT_PROTECTION_UNDESIRED) {
			hdcp->value = DRM_MODE_CONTENT_PROTECTION_ENABLED;
			schedule_work(&hdcp->prop_work);
		}
		goto out;
	}

	DRM_DEBUG_KMS("[%s:%d] HDCP link failed, retrying authentication\n",
		      connector->base.name, connector->base.base.id);

	ret = _intel_hdcp_disable(connector);
	if (ret) {
		DRM_ERROR("Failed to disable hdcp (%d)\n", ret);
		hdcp->value = DRM_MODE_CONTENT_PROTECTION_DESIRED;
		schedule_work(&hdcp->prop_work);
		goto out;
	}

	ret = _intel_hdcp_enable(connector);
	if (ret) {
		DRM_ERROR("Failed to enable hdcp (%d)\n", ret);
		hdcp->value = DRM_MODE_CONTENT_PROTECTION_DESIRED;
		schedule_work(&hdcp->prop_work);
		goto out;
	}

out:
	mutex_unlock(&hdcp->mutex);
	return ret;
}