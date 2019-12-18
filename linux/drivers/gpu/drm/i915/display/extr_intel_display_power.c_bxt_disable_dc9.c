#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_STATE_DISABLE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  assert_can_disable_dc9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_set_dc_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_pps_unlock_regs_wa (struct drm_i915_private*) ; 

__attribute__((used)) static void bxt_disable_dc9(struct drm_i915_private *dev_priv)
{
	assert_can_disable_dc9(dev_priv);

	DRM_DEBUG_KMS("Disabling DC9\n");

	gen9_set_dc_state(dev_priv, DC_STATE_DISABLE);

	intel_pps_unlock_regs_wa(dev_priv);
}