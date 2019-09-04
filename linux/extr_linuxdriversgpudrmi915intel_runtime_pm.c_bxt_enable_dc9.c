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
 int /*<<< orphan*/  DC_STATE_EN_DC9 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  assert_can_enable_dc9 (struct drm_i915_private*) ; 
 int /*<<< orphan*/  gen9_set_dc_state (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_power_sequencer_reset (struct drm_i915_private*) ; 

void bxt_enable_dc9(struct drm_i915_private *dev_priv)
{
	assert_can_enable_dc9(dev_priv);

	DRM_DEBUG_KMS("Enabling DC9\n");

	intel_power_sequencer_reset(dev_priv);
	gen9_set_dc_state(dev_priv, DC_STATE_EN_DC9);
}