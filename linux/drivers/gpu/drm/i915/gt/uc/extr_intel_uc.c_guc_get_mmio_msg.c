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
typedef  int u32 ;
struct intel_guc {int mmio_msg; int msg_enabled_mask; int /*<<< orphan*/  irq_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  uncore; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOFT_SCRATCH (int) ; 
 int /*<<< orphan*/  guc_clear_mmio_msg (struct intel_guc*) ; 
 TYPE_1__* guc_to_gt (struct intel_guc*) ; 
 int intel_uncore_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void guc_get_mmio_msg(struct intel_guc *guc)
{
	u32 val;

	spin_lock_irq(&guc->irq_lock);

	val = intel_uncore_read(guc_to_gt(guc)->uncore, SOFT_SCRATCH(15));
	guc->mmio_msg |= val & guc->msg_enabled_mask;

	/*
	 * clear all events, including the ones we're not currently servicing,
	 * to make sure we don't try to process a stale message if we enable
	 * handling of more events later.
	 */
	guc_clear_mmio_msg(guc);

	spin_unlock_irq(&guc->irq_lock);
}