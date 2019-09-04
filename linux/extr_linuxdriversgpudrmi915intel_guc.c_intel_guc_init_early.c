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
struct intel_guc {int /*<<< orphan*/  notify; int /*<<< orphan*/  handler; int /*<<< orphan*/  send; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  send_mutex; int /*<<< orphan*/  log; int /*<<< orphan*/  ct; } ;

/* Variables and functions */
 int /*<<< orphan*/  gen8_guc_raise_irq ; 
 int /*<<< orphan*/  intel_guc_ct_init_early (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_guc_fw_init_early (struct intel_guc*) ; 
 int /*<<< orphan*/  intel_guc_log_init_early (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_guc_send_nop ; 
 int /*<<< orphan*/  intel_guc_to_host_event_handler_nop ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void intel_guc_init_early(struct intel_guc *guc)
{
	intel_guc_fw_init_early(guc);
	intel_guc_ct_init_early(&guc->ct);
	intel_guc_log_init_early(&guc->log);

	mutex_init(&guc->send_mutex);
	spin_lock_init(&guc->irq_lock);
	guc->send = intel_guc_send_nop;
	guc->handler = intel_guc_to_host_event_handler_nop;
	guc->notify = gen8_guc_raise_irq;
}