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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  flush_work; } ;
struct intel_guc_log {TYPE_1__ relay; int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  guc_log_enable_flush_events (struct intel_guc_log*) ; 
 int guc_log_map (struct intel_guc_log*) ; 
 int guc_log_relay_create (struct intel_guc_log*) ; 
 int /*<<< orphan*/  guc_log_relay_destroy (struct intel_guc_log*) ; 
 int /*<<< orphan*/  i915_has_memcpy_from_wc () ; 
 scalar_t__ intel_guc_log_relay_enabled (struct intel_guc_log*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_highpri_wq ; 

int intel_guc_log_relay_open(struct intel_guc_log *log)
{
	int ret;

	if (!log->vma)
		return -ENODEV;

	mutex_lock(&log->relay.lock);

	if (intel_guc_log_relay_enabled(log)) {
		ret = -EEXIST;
		goto out_unlock;
	}

	/*
	 * We require SSE 4.1 for fast reads from the GuC log buffer and
	 * it should be present on the chipsets supporting GuC based
	 * submisssions.
	 */
	if (!i915_has_memcpy_from_wc()) {
		ret = -ENXIO;
		goto out_unlock;
	}

	ret = guc_log_relay_create(log);
	if (ret)
		goto out_unlock;

	ret = guc_log_map(log);
	if (ret)
		goto out_relay;

	mutex_unlock(&log->relay.lock);

	guc_log_enable_flush_events(log);

	/*
	 * When GuC is logging without us relaying to userspace, we're ignoring
	 * the flush notification. This means that we need to unconditionally
	 * flush on relay enabling, since GuC only notifies us once.
	 */
	queue_work(system_highpri_wq, &log->relay.flush_work);

	return 0;

out_relay:
	guc_log_relay_destroy(log);
out_unlock:
	mutex_unlock(&log->relay.lock);

	return ret;
}