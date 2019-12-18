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
typedef  int /*<<< orphan*/  uint_fixed_16_16_t ;
typedef  int u32 ;
struct TYPE_2__ {struct drm_atomic_state* state; } ;
struct intel_crtc_state {TYPE_1__ base; } ;
struct drm_i915_private {scalar_t__ ipc_enabled; } ;
struct drm_atomic_state {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int fixed16_to_u32_round_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_get_linetime_us (struct intel_crtc_state const*) ; 
 int /*<<< orphan*/  mul_u32_fixed16 (int,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
skl_compute_linetime_wm(const struct intel_crtc_state *crtc_state)
{
	struct drm_atomic_state *state = crtc_state->base.state;
	struct drm_i915_private *dev_priv = to_i915(state->dev);
	uint_fixed_16_16_t linetime_us;
	u32 linetime_wm;

	linetime_us = intel_get_linetime_us(crtc_state);
	linetime_wm = fixed16_to_u32_round_up(mul_u32_fixed16(8, linetime_us));

	/* Display WA #1135: BXT:ALL GLK:ALL */
	if (IS_GEN9_LP(dev_priv) && dev_priv->ipc_enabled)
		linetime_wm /= 2;

	return linetime_wm;
}