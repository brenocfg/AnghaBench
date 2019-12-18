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
struct intel_hdcp {int hdcp_encrypted; TYPE_5__* shim; } ;
struct TYPE_7__ {int port; } ;
struct intel_digital_port {TYPE_2__ base; } ;
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_3__ base; int /*<<< orphan*/  name; TYPE_1__* dev; } ;
struct intel_connector {TYPE_4__ base; struct intel_hdcp hdcp; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_10__ {int (* toggle_signalling ) (struct intel_digital_port*,int) ;} ;
struct TYPE_6__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  ENCRYPT_STATUS_CHANGE_TIMEOUT_MS ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_HDCP_CONF (int) ; 
 int /*<<< orphan*/  PORT_HDCP_STATUS (int) ; 
 struct intel_digital_port* conn_to_dig_port (struct intel_connector*) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct intel_digital_port*,int) ; 

__attribute__((used)) static int _intel_hdcp_disable(struct intel_connector *connector)
{
	struct intel_hdcp *hdcp = &connector->hdcp;
	struct drm_i915_private *dev_priv = connector->base.dev->dev_private;
	struct intel_digital_port *intel_dig_port = conn_to_dig_port(connector);
	enum port port = intel_dig_port->base.port;
	int ret;

	DRM_DEBUG_KMS("[%s:%d] HDCP is being disabled...\n",
		      connector->base.name, connector->base.base.id);

	hdcp->hdcp_encrypted = false;
	I915_WRITE(PORT_HDCP_CONF(port), 0);
	if (intel_de_wait_for_clear(dev_priv, PORT_HDCP_STATUS(port), ~0,
				    ENCRYPT_STATUS_CHANGE_TIMEOUT_MS)) {
		DRM_ERROR("Failed to disable HDCP, timeout clearing status\n");
		return -ETIMEDOUT;
	}

	ret = hdcp->shim->toggle_signalling(intel_dig_port, false);
	if (ret) {
		DRM_ERROR("Failed to disable HDCP signalling\n");
		return ret;
	}

	DRM_DEBUG_KMS("HDCP is disabled\n");
	return 0;
}