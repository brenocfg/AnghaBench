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
 int /*<<< orphan*/  CONFIG_DRM_I915_DEBUG ; 
 int /*<<< orphan*/  CONFIG_DRM_I915_DEBUG_GEM ; 
 int GUC_LOG_LEVEL_DISABLED ; 
 int GUC_LOG_LEVEL_MAX ; 
 int GUC_LOG_LEVEL_NON_VERBOSE ; 
 int /*<<< orphan*/  HAS_GUC (struct drm_i915_private*) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_is_using_guc () ; 

__attribute__((used)) static int __get_default_guc_log_level(struct drm_i915_private *i915)
{
	int guc_log_level;

	if (!HAS_GUC(i915) || !intel_uc_is_using_guc())
		guc_log_level = GUC_LOG_LEVEL_DISABLED;
	else if (IS_ENABLED(CONFIG_DRM_I915_DEBUG) ||
		 IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM))
		guc_log_level = GUC_LOG_LEVEL_MAX;
	else
		guc_log_level = GUC_LOG_LEVEL_NON_VERBOSE;

	/* Any platform specific fine-tuning can be done here */

	return guc_log_level;
}