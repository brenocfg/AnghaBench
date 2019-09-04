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
struct intel_guc_log {scalar_t__ level; int /*<<< orphan*/  vma; } ;
struct intel_guc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  struct_mutex; } ;
struct drm_i915_private {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 scalar_t__ GUC_LOG_LEVEL_DISABLED ; 
 int /*<<< orphan*/  GUC_LOG_LEVEL_IS_ENABLED (scalar_t__) ; 
 int /*<<< orphan*/  GUC_LOG_LEVEL_IS_VERBOSE (scalar_t__) ; 
 scalar_t__ GUC_LOG_LEVEL_MAX ; 
 int /*<<< orphan*/  GUC_LOG_LEVEL_TO_VERBOSITY (scalar_t__) ; 
 scalar_t__ GUC_LOG_VERBOSITY_MIN ; 
 int guc_action_control_log (struct intel_guc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 struct intel_guc* log_to_guc (struct intel_guc_log*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int intel_guc_log_set_level(struct intel_guc_log *log, u32 level)
{
	struct intel_guc *guc = log_to_guc(log);
	struct drm_i915_private *dev_priv = guc_to_i915(guc);
	int ret;

	BUILD_BUG_ON(GUC_LOG_VERBOSITY_MIN != 0);
	GEM_BUG_ON(!log->vma);

	/*
	 * GuC is recognizing log levels starting from 0 to max, we're using 0
	 * as indication that logging should be disabled.
	 */
	if (level < GUC_LOG_LEVEL_DISABLED || level > GUC_LOG_LEVEL_MAX)
		return -EINVAL;

	mutex_lock(&dev_priv->drm.struct_mutex);

	if (log->level == level) {
		ret = 0;
		goto out_unlock;
	}

	intel_runtime_pm_get(dev_priv);
	ret = guc_action_control_log(guc, GUC_LOG_LEVEL_IS_VERBOSE(level),
				     GUC_LOG_LEVEL_IS_ENABLED(level),
				     GUC_LOG_LEVEL_TO_VERBOSITY(level));
	intel_runtime_pm_put(dev_priv);
	if (ret) {
		DRM_DEBUG_DRIVER("guc_log_control action failed %d\n", ret);
		goto out_unlock;
	}

	log->level = level;

out_unlock:
	mutex_unlock(&dev_priv->drm.struct_mutex);

	return ret;
}