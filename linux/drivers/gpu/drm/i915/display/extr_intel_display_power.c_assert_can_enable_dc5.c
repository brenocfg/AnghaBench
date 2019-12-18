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
struct drm_i915_private {int /*<<< orphan*/  runtime_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_STATE_EN ; 
 int DC_STATE_EN_UPTO_DC5 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SKL_DISP_PW_2 ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  assert_csr_loaded (struct drm_i915_private*) ; 
 int /*<<< orphan*/  assert_rpm_wakelock_held (int /*<<< orphan*/ *) ; 
 int intel_display_power_well_is_enabled (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assert_can_enable_dc5(struct drm_i915_private *dev_priv)
{
	bool pg2_enabled = intel_display_power_well_is_enabled(dev_priv,
					SKL_DISP_PW_2);

	WARN_ONCE(pg2_enabled, "PG2 not disabled to enable DC5.\n");

	WARN_ONCE((I915_READ(DC_STATE_EN) & DC_STATE_EN_UPTO_DC5),
		  "DC5 already programmed to be enabled.\n");
	assert_rpm_wakelock_held(&dev_priv->runtime_pm);

	assert_csr_loaded(dev_priv);
}