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
struct TYPE_3__ {int cdclk; void* voltage_level; } ;
struct TYPE_4__ {TYPE_1__ logical; TYPE_1__ actual; } ;
struct intel_atomic_state {TYPE_2__ cdclk; int /*<<< orphan*/  active_crtcs; } ;
struct drm_i915_private {int dummy; } ;
struct drm_atomic_state {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int intel_compute_min_cdclk (struct drm_atomic_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_atomic_state* to_intel_atomic_state (struct drm_atomic_state*) ; 
 int vlv_calc_cdclk (struct drm_i915_private*,int) ; 
 void* vlv_calc_voltage_level (struct drm_i915_private*,int) ; 

__attribute__((used)) static int vlv_modeset_calc_cdclk(struct drm_atomic_state *state)
{
	struct drm_i915_private *dev_priv = to_i915(state->dev);
	struct intel_atomic_state *intel_state = to_intel_atomic_state(state);
	int min_cdclk, cdclk;

	min_cdclk = intel_compute_min_cdclk(state);
	if (min_cdclk < 0)
		return min_cdclk;

	cdclk = vlv_calc_cdclk(dev_priv, min_cdclk);

	intel_state->cdclk.logical.cdclk = cdclk;
	intel_state->cdclk.logical.voltage_level =
		vlv_calc_voltage_level(dev_priv, cdclk);

	if (!intel_state->active_crtcs) {
		cdclk = vlv_calc_cdclk(dev_priv, 0);

		intel_state->cdclk.actual.cdclk = cdclk;
		intel_state->cdclk.actual.voltage_level =
			vlv_calc_voltage_level(dev_priv, cdclk);
	} else {
		intel_state->cdclk.actual =
			intel_state->cdclk.logical;
	}

	return 0;
}