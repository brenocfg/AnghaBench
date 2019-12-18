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
struct TYPE_2__ {int /*<<< orphan*/  saveFBC_CONTROL; int /*<<< orphan*/  saveDSPARB; } ;
struct drm_i915_private {TYPE_1__ regfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSPARB ; 
 int /*<<< orphan*/  FBC_CONTROL ; 
 scalar_t__ HAS_FBC (struct drm_i915_private*) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int /*<<< orphan*/  IS_G4X (struct drm_i915_private*) ; 
 int /*<<< orphan*/  i915_redisable_vga (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_fbc_global_disable (struct drm_i915_private*) ; 

__attribute__((used)) static void i915_restore_display(struct drm_i915_private *dev_priv)
{
	/* Display arbitration */
	if (INTEL_GEN(dev_priv) <= 4)
		I915_WRITE(DSPARB, dev_priv->regfile.saveDSPARB);

	/* only restore FBC info on the platform that supports FBC*/
	intel_fbc_global_disable(dev_priv);

	/* restore FBC interval */
	if (HAS_FBC(dev_priv) && INTEL_GEN(dev_priv) <= 4 && !IS_G4X(dev_priv))
		I915_WRITE(FBC_CONTROL, dev_priv->regfile.saveFBC_CONTROL);

	i915_redisable_vga(dev_priv);
}