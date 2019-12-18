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
typedef  scalar_t__ u8 ;
struct intel_rps {scalar_t__ max_freq; scalar_t__ min_freq; scalar_t__ cur_freq; int /*<<< orphan*/  enabled; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct intel_rps rps; } ;
struct drm_i915_private {TYPE_1__ gt_pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int gen6_set_rps (struct drm_i915_private*,scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int valleyview_set_rps (struct drm_i915_private*,scalar_t__) ; 

int intel_set_rps(struct drm_i915_private *dev_priv, u8 val)
{
	struct intel_rps *rps = &dev_priv->gt_pm.rps;
	int err;

	lockdep_assert_held(&rps->lock);
	GEM_BUG_ON(val > rps->max_freq);
	GEM_BUG_ON(val < rps->min_freq);

	if (!rps->enabled) {
		rps->cur_freq = val;
		return 0;
	}

	if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv))
		err = valleyview_set_rps(dev_priv, val);
	else
		err = gen6_set_rps(dev_priv, val);

	return err;
}