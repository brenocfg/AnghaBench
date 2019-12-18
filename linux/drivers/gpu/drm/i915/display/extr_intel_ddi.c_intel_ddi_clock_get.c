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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct intel_encoder {TYPE_1__ base; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  bxt_ddi_clock_get (struct intel_encoder*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  cnl_ddi_clock_get (struct intel_encoder*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  hsw_ddi_clock_get (struct intel_encoder*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  icl_ddi_clock_get (struct intel_encoder*,struct intel_crtc_state*) ; 
 int /*<<< orphan*/  skl_ddi_clock_get (struct intel_encoder*,struct intel_crtc_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_ddi_clock_get(struct intel_encoder *encoder,
				struct intel_crtc_state *pipe_config)
{
	struct drm_i915_private *dev_priv = to_i915(encoder->base.dev);

	if (INTEL_GEN(dev_priv) >= 11)
		icl_ddi_clock_get(encoder, pipe_config);
	else if (IS_CANNONLAKE(dev_priv))
		cnl_ddi_clock_get(encoder, pipe_config);
	else if (IS_GEN9_LP(dev_priv))
		bxt_ddi_clock_get(encoder, pipe_config);
	else if (IS_GEN9_BC(dev_priv))
		skl_ddi_clock_get(encoder, pipe_config);
	else if (INTEL_GEN(dev_priv) <= 8)
		hsw_ddi_clock_get(encoder, pipe_config);
}