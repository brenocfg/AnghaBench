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
struct intel_wm_level {int enable; scalar_t__ fbc_val; } ;
struct intel_wm_config {int num_pipes_active; } ;
struct intel_pipe_wm {int fbc_wm_enabled; struct intel_wm_level* wm; } ;
struct ilk_wm_maximums {scalar_t__ fbc; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_GEN (struct drm_i915_private*,int) ; 
 scalar_t__ IS_IVYBRIDGE (struct drm_i915_private*) ; 
 int /*<<< orphan*/  ilk_merge_wm_level (struct drm_i915_private*,int,struct intel_wm_level*) ; 
 int /*<<< orphan*/  ilk_validate_wm_level (int,struct ilk_wm_maximums const*,struct intel_wm_level*) ; 
 int ilk_wm_max_level (struct drm_i915_private*) ; 
 scalar_t__ intel_fbc_is_active (struct drm_i915_private*) ; 

__attribute__((used)) static void ilk_wm_merge(struct drm_i915_private *dev_priv,
			 const struct intel_wm_config *config,
			 const struct ilk_wm_maximums *max,
			 struct intel_pipe_wm *merged)
{
	int level, max_level = ilk_wm_max_level(dev_priv);
	int last_enabled_level = max_level;

	/* ILK/SNB/IVB: LP1+ watermarks only w/ single pipe */
	if ((INTEL_GEN(dev_priv) <= 6 || IS_IVYBRIDGE(dev_priv)) &&
	    config->num_pipes_active > 1)
		last_enabled_level = 0;

	/* ILK: FBC WM must be disabled always */
	merged->fbc_wm_enabled = INTEL_GEN(dev_priv) >= 6;

	/* merge each WM1+ level */
	for (level = 1; level <= max_level; level++) {
		struct intel_wm_level *wm = &merged->wm[level];

		ilk_merge_wm_level(dev_priv, level, wm);

		if (level > last_enabled_level)
			wm->enable = false;
		else if (!ilk_validate_wm_level(level, max, wm))
			/* make sure all following levels get disabled */
			last_enabled_level = level - 1;

		/*
		 * The spec says it is preferred to disable
		 * FBC WMs instead of disabling a WM level.
		 */
		if (wm->fbc_val > max->fbc) {
			if (wm->enable)
				merged->fbc_wm_enabled = false;
			wm->fbc_val = 0;
		}
	}

	/* ILK: LP2+ must be disabled when FBC WM is disabled but FBC enabled */
	/*
	 * FIXME this is racy. FBC might get enabled later.
	 * What we should check here is whether FBC can be
	 * enabled sometime later.
	 */
	if (IS_GEN(dev_priv, 5) && !merged->fbc_wm_enabled &&
	    intel_fbc_is_active(dev_priv)) {
		for (level = 2; level <= max_level; level++) {
			struct intel_wm_level *wm = &merged->wm[level];

			wm->enable = false;
		}
	}
}