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
typedef  int /*<<< orphan*/  u32 ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  GEN11_GRDOM_GUC ; 
 int /*<<< orphan*/  GEN9_GRDOM_GUC ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 int gen6_hw_domain_reset (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get (struct drm_i915_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put (struct drm_i915_private*,int /*<<< orphan*/ ) ; 

int intel_reset_guc(struct drm_i915_private *dev_priv)
{
	u32 guc_domain = INTEL_GEN(dev_priv) >= 11 ? GEN11_GRDOM_GUC :
						     GEN9_GRDOM_GUC;
	int ret;

	GEM_BUG_ON(!HAS_GUC(dev_priv));

	intel_uncore_forcewake_get(dev_priv, FORCEWAKE_ALL);
	ret = gen6_hw_domain_reset(dev_priv, guc_domain);
	intel_uncore_forcewake_put(dev_priv, FORCEWAKE_ALL);

	return ret;
}