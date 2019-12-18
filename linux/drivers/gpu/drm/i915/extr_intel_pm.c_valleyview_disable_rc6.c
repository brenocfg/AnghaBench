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
struct drm_i915_private {int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEN6_RC_CONTROL ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void valleyview_disable_rc6(struct drm_i915_private *dev_priv)
{
	/* We're doing forcewake before Disabling RC6,
	 * This what the BIOS expects when going into suspend */
	intel_uncore_forcewake_get(&dev_priv->uncore, FORCEWAKE_ALL);

	I915_WRITE(GEN6_RC_CONTROL, 0);

	intel_uncore_forcewake_put(&dev_priv->uncore, FORCEWAKE_ALL);
}