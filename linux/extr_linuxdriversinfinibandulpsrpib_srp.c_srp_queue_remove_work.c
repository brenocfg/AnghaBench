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
struct srp_target_port {scalar_t__ state; int /*<<< orphan*/  remove_work; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ SRP_TARGET_REMOVED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_remove_wq ; 

__attribute__((used)) static bool srp_queue_remove_work(struct srp_target_port *target)
{
	bool changed = false;

	spin_lock_irq(&target->lock);
	if (target->state != SRP_TARGET_REMOVED) {
		target->state = SRP_TARGET_REMOVED;
		changed = true;
	}
	spin_unlock_irq(&target->lock);

	if (changed)
		queue_work(srp_remove_wq, &target->remove_work);

	return changed;
}