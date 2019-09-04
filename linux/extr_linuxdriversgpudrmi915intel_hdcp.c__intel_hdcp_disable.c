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
struct TYPE_10__ {int port; } ;
struct intel_digital_port {TYPE_5__ base; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {TYPE_1__ base; int /*<<< orphan*/  name; TYPE_3__* dev; } ;
struct intel_connector {TYPE_2__* hdcp_shim; TYPE_4__ base; } ;
struct drm_i915_private {int dummy; } ;
typedef  enum port { ____Placeholder_port } port ;
struct TYPE_8__ {struct drm_i915_private* dev_private; } ;
struct TYPE_7__ {int (* toggle_signalling ) (struct intel_digital_port*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PORT_HDCP_CONF (int) ; 
 int /*<<< orphan*/  PORT_HDCP_STATUS (int) ; 
 struct intel_digital_port* conn_to_dig_port (struct intel_connector*) ; 
 scalar_t__ intel_wait_for_register (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct intel_digital_port*,int) ; 

__attribute__((used)) static int _intel_hdcp_disable(struct intel_connector *connector)
{
	struct drm_i915_private *dev_priv = connector->base.dev->dev_private;
	struct intel_digital_port *intel_dig_port = conn_to_dig_port(connector);
	enum port port = intel_dig_port->base.port;
	int ret;

	DRM_DEBUG_KMS("[%s:%d] HDCP is being disabled...\n",
		      connector->base.name, connector->base.base.id);

	I915_WRITE(PORT_HDCP_CONF(port), 0);
	if (intel_wait_for_register(dev_priv, PORT_HDCP_STATUS(port), ~0, 0,
				    20)) {
		DRM_ERROR("Failed to disable HDCP, timeout clearing status\n");
		return -ETIMEDOUT;
	}

	ret = connector->hdcp_shim->toggle_signalling(intel_dig_port, false);
	if (ret) {
		DRM_ERROR("Failed to disable HDCP signalling\n");
		return ret;
	}

	DRM_DEBUG_KMS("HDCP is disabled\n");
	return 0;
}