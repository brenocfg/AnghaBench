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
struct intel_guc_log {int dummy; } ;
struct intel_guc {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  guc_action_flush_log_complete (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_read_update_log_buffer (struct intel_guc_log*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 struct intel_guc* log_to_guc (struct intel_guc_log*) ; 

__attribute__((used)) static void guc_log_capture_logs(struct intel_guc_log *log)
{
	struct intel_guc *guc = log_to_guc(log);
	struct drm_i915_private *dev_priv = guc_to_i915(guc);

	guc_read_update_log_buffer(log);

	/*
	 * Generally device is expected to be active only at this
	 * time, so get/put should be really quick.
	 */
	intel_runtime_pm_get(dev_priv);
	guc_action_flush_log_complete(guc);
	intel_runtime_pm_put(dev_priv);
}