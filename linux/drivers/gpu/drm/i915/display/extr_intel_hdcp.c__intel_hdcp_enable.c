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
struct intel_hdcp {int hdcp_encrypted; } ;
struct TYPE_5__ {int id; } ;
struct TYPE_6__ {int name; TYPE_2__ base; TYPE_1__* dev; } ;
struct intel_connector {TYPE_3__ base; struct intel_hdcp hdcp; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_4__ {struct drm_i915_private* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int ENXIO ; 
 int KEY_LOAD_TRIES ; 
 int /*<<< orphan*/  _intel_hdcp_disable (struct intel_connector*) ; 
 int /*<<< orphan*/  hdcp_key_loadable (struct drm_i915_private*) ; 
 int intel_hdcp_auth (struct intel_connector*) ; 
 int /*<<< orphan*/  intel_hdcp_clear_keys (struct drm_i915_private*) ; 
 int intel_hdcp_load_keys (struct drm_i915_private*) ; 

__attribute__((used)) static int _intel_hdcp_enable(struct intel_connector *connector)
{
	struct intel_hdcp *hdcp = &connector->hdcp;
	struct drm_i915_private *dev_priv = connector->base.dev->dev_private;
	int i, ret, tries = 3;

	DRM_DEBUG_KMS("[%s:%d] HDCP is being enabled...\n",
		      connector->base.name, connector->base.base.id);

	if (!hdcp_key_loadable(dev_priv)) {
		DRM_ERROR("HDCP key Load is not possible\n");
		return -ENXIO;
	}

	for (i = 0; i < KEY_LOAD_TRIES; i++) {
		ret = intel_hdcp_load_keys(dev_priv);
		if (!ret)
			break;
		intel_hdcp_clear_keys(dev_priv);
	}
	if (ret) {
		DRM_ERROR("Could not load HDCP keys, (%d)\n", ret);
		return ret;
	}

	/* Incase of authentication failures, HDCP spec expects reauth. */
	for (i = 0; i < tries; i++) {
		ret = intel_hdcp_auth(connector);
		if (!ret) {
			hdcp->hdcp_encrypted = true;
			return 0;
		}

		DRM_DEBUG_KMS("HDCP Auth failure (%d)\n", ret);

		/* Ensuring HDCP encryption and signalling are stopped. */
		_intel_hdcp_disable(connector);
	}

	DRM_DEBUG_KMS("HDCP authentication failed (%d tries/%d)\n", tries, ret);
	return ret;
}