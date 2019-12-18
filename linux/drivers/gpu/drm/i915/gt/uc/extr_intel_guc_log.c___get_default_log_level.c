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
typedef  scalar_t__ u32 ;
struct intel_guc_log {int dummy; } ;
struct TYPE_2__ {scalar_t__ guc_log_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_DRM_I915_DEBUG ; 
 int /*<<< orphan*/  CONFIG_DRM_I915_DEBUG_GEM ; 
 int /*<<< orphan*/  DRM_WARN (char*,char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GUC_LOG_LEVEL_DISABLED ; 
 scalar_t__ GUC_LOG_LEVEL_MAX ; 
 scalar_t__ GUC_LOG_LEVEL_NON_VERBOSE ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 TYPE_1__ i915_modparams ; 

__attribute__((used)) static u32 __get_default_log_level(struct intel_guc_log *log)
{
	/* A negative value means "use platform/config default" */
	if (i915_modparams.guc_log_level < 0) {
		return (IS_ENABLED(CONFIG_DRM_I915_DEBUG) ||
			IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM)) ?
			GUC_LOG_LEVEL_MAX : GUC_LOG_LEVEL_NON_VERBOSE;
	}

	if (i915_modparams.guc_log_level > GUC_LOG_LEVEL_MAX) {
		DRM_WARN("Incompatible option detected: %s=%d, %s!\n",
			 "guc_log_level", i915_modparams.guc_log_level,
			 "verbosity too high");
		return (IS_ENABLED(CONFIG_DRM_I915_DEBUG) ||
			IS_ENABLED(CONFIG_DRM_I915_DEBUG_GEM)) ?
			GUC_LOG_LEVEL_MAX : GUC_LOG_LEVEL_DISABLED;
	}

	GEM_BUG_ON(i915_modparams.guc_log_level < GUC_LOG_LEVEL_DISABLED);
	GEM_BUG_ON(i915_modparams.guc_log_level > GUC_LOG_LEVEL_MAX);
	return i915_modparams.guc_log_level;
}