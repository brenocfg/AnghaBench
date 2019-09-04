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
struct TYPE_2__ {int /*<<< orphan*/  flush_work; } ;
struct intel_guc_log {TYPE_1__ relay; } ;
struct intel_guc {int dummy; } ;
struct drm_i915_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  guc_action_flush_log (struct intel_guc*) ; 
 int /*<<< orphan*/  guc_log_capture_logs (struct intel_guc_log*) ; 
 struct drm_i915_private* guc_to_i915 (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_runtime_pm_get (struct drm_i915_private*) ; 
 int /*<<< orphan*/  intel_runtime_pm_put (struct drm_i915_private*) ; 
 struct intel_guc* log_to_guc (struct intel_guc_log*) ; 

void intel_guc_log_relay_flush(struct intel_guc_log *log)
{
	struct intel_guc *guc = log_to_guc(log);
	struct drm_i915_private *i915 = guc_to_i915(guc);

	/*
	 * Before initiating the forceful flush, wait for any pending/ongoing
	 * flush to complete otherwise forceful flush may not actually happen.
	 */
	flush_work(&log->relay.flush_work);

	intel_runtime_pm_get(i915);
	guc_action_flush_log(guc);
	intel_runtime_pm_put(i915);

	/* GuC would have updated log buffer by now, so capture it */
	guc_log_capture_logs(log);
}