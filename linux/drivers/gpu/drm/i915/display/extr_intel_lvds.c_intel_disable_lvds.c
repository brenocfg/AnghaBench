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
struct intel_lvds_encoder {int /*<<< orphan*/  reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int LVDS_PORT_EN ; 
 int PANEL_POWER_ON ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PP_CONTROL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PP_ON ; 
 int /*<<< orphan*/  PP_STATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_de_wait_for_clear (struct drm_i915_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_lvds_encoder* to_lvds_encoder (TYPE_1__*) ; 

__attribute__((used)) static void intel_disable_lvds(struct intel_encoder *encoder,
			       const struct intel_crtc_state *old_crtc_state,
			       const struct drm_connector_state *old_conn_state)
{
	struct intel_lvds_encoder *lvds_encoder = to_lvds_encoder(&encoder->base);
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);

	I915_WRITE(PP_CONTROL(0), I915_READ(PP_CONTROL(0)) & ~PANEL_POWER_ON);
	if (intel_de_wait_for_clear(dev_priv, PP_STATUS(0), PP_ON, 1000))
		DRM_ERROR("timed out waiting for panel to power off\n");

	I915_WRITE(lvds_encoder->reg, I915_READ(lvds_encoder->reg) & ~LVDS_PORT_EN);
	POSTING_READ(lvds_encoder->reg);
}