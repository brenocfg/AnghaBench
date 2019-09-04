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
struct intel_encoder {TYPE_1__ base; } ;
struct intel_dp {int /*<<< orphan*/  aux_power_domain; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_connector {scalar_t__ status; int /*<<< orphan*/  name; TYPE_2__ base; } ;
struct TYPE_6__ {struct intel_encoder base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ connector_status_connected ; 
 TYPE_3__* dp_to_dig_port (struct intel_dp*) ; 
 struct intel_dp* intel_attached_dp (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_display_power_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_display_power_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_set_edid (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_unset_edid (struct intel_dp*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intel_dp_force(struct drm_connector *connector)
{
	struct intel_dp *intel_dp = intel_attached_dp(connector);
	struct intel_encoder *intel_encoder = &dp_to_dig_port(intel_dp)->base;
	struct drm_i915_private *dev_priv = to_i915(intel_encoder->base.dev);

	DRM_DEBUG_KMS("[CONNECTOR:%d:%s]\n",
		      connector->base.id, connector->name);
	intel_dp_unset_edid(intel_dp);

	if (connector->status != connector_status_connected)
		return;

	intel_display_power_get(dev_priv, intel_dp->aux_power_domain);

	intel_dp_set_edid(intel_dp);

	intel_display_power_put(dev_priv, intel_dp->aux_power_domain);
}