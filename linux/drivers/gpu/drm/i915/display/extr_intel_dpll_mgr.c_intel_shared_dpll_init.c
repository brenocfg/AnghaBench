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
struct intel_dpll_mgr {struct dpll_info* dpll_info; } ;
struct drm_i915_private {int num_shared_dpll; int /*<<< orphan*/  dpll_lock; struct intel_dpll_mgr const* dpll_mgr; TYPE_1__* shared_dplls; } ;
struct drm_device {int dummy; } ;
struct dpll_info {int id; scalar_t__ name; } ;
struct TYPE_2__ {struct dpll_info const* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ HAS_DDI (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_CPT (struct drm_i915_private*) ; 
 scalar_t__ HAS_PCH_IBX (struct drm_i915_private*) ; 
 int I915_NUM_PLLS ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_ELKHARTLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_BC (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN9_LP (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct intel_dpll_mgr bxt_pll_mgr ; 
 struct intel_dpll_mgr cnl_pll_mgr ; 
 struct intel_dpll_mgr ehl_pll_mgr ; 
 struct intel_dpll_mgr hsw_pll_mgr ; 
 struct intel_dpll_mgr icl_pll_mgr ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct intel_dpll_mgr pch_pll_mgr ; 
 struct intel_dpll_mgr skl_pll_mgr ; 
 struct intel_dpll_mgr tgl_pll_mgr ; 
 struct drm_i915_private* to_i915 (struct drm_device*) ; 

void intel_shared_dpll_init(struct drm_device *dev)
{
	struct drm_i915_private *dev_priv = to_i915(dev);
	const struct intel_dpll_mgr *dpll_mgr = NULL;
	const struct dpll_info *dpll_info;
	int i;

	if (INTEL_GEN(dev_priv) >= 12)
		dpll_mgr = &tgl_pll_mgr;
	else if (IS_ELKHARTLAKE(dev_priv))
		dpll_mgr = &ehl_pll_mgr;
	else if (INTEL_GEN(dev_priv) >= 11)
		dpll_mgr = &icl_pll_mgr;
	else if (IS_CANNONLAKE(dev_priv))
		dpll_mgr = &cnl_pll_mgr;
	else if (IS_GEN9_BC(dev_priv))
		dpll_mgr = &skl_pll_mgr;
	else if (IS_GEN9_LP(dev_priv))
		dpll_mgr = &bxt_pll_mgr;
	else if (HAS_DDI(dev_priv))
		dpll_mgr = &hsw_pll_mgr;
	else if (HAS_PCH_IBX(dev_priv) || HAS_PCH_CPT(dev_priv))
		dpll_mgr = &pch_pll_mgr;

	if (!dpll_mgr) {
		dev_priv->num_shared_dpll = 0;
		return;
	}

	dpll_info = dpll_mgr->dpll_info;

	for (i = 0; dpll_info[i].name; i++) {
		WARN_ON(i != dpll_info[i].id);
		dev_priv->shared_dplls[i].info = &dpll_info[i];
	}

	dev_priv->dpll_mgr = dpll_mgr;
	dev_priv->num_shared_dpll = i;
	mutex_init(&dev_priv->dpll_lock);

	BUG_ON(dev_priv->num_shared_dpll > I915_NUM_PLLS);
}