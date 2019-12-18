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
struct intel_pipe_wm {scalar_t__ fbc_wm_enabled; TYPE_1__* wm; } ;
struct drm_i915_private {int dummy; } ;
struct TYPE_2__ {scalar_t__ enable; } ;

/* Variables and functions */
 int ilk_wm_max_level (struct drm_i915_private*) ; 

__attribute__((used)) static struct intel_pipe_wm *
ilk_find_best_result(struct drm_i915_private *dev_priv,
		     struct intel_pipe_wm *r1,
		     struct intel_pipe_wm *r2)
{
	int level, max_level = ilk_wm_max_level(dev_priv);
	int level1 = 0, level2 = 0;

	for (level = 1; level <= max_level; level++) {
		if (r1->wm[level].enable)
			level1 = level;
		if (r2->wm[level].enable)
			level2 = level;
	}

	if (level1 == level2) {
		if (r2->fbc_wm_enabled && !r1->fbc_wm_enabled)
			return r2;
		else
			return r1;
	} else if (level1 > level2) {
		return r1;
	} else {
		return r2;
	}
}