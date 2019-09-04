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
struct intel_guc_log {TYPE_1__ relay; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  guc_log_disable_flush_events (struct intel_guc_log*) ; 
 int /*<<< orphan*/  guc_log_relay_destroy (struct intel_guc_log*) ; 
 int /*<<< orphan*/  guc_log_unmap (struct intel_guc_log*) ; 
 int /*<<< orphan*/  intel_guc_log_relay_enabled (struct intel_guc_log*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void intel_guc_log_relay_close(struct intel_guc_log *log)
{
	guc_log_disable_flush_events(log);
	flush_work(&log->relay.flush_work);

	mutex_lock(&log->relay.lock);
	GEM_BUG_ON(!intel_guc_log_relay_enabled(log));
	guc_log_unmap(log);
	guc_log_relay_destroy(log);
	mutex_unlock(&log->relay.lock);
}