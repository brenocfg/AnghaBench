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
struct intel_uncore {TYPE_1__* debug; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int check_for_unclaimed_mmio (struct intel_uncore*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

bool intel_uncore_unclaimed_mmio(struct intel_uncore *uncore)
{
	bool ret;

	spin_lock_irq(&uncore->debug->lock);
	ret = check_for_unclaimed_mmio(uncore);
	spin_unlock_irq(&uncore->debug->lock);

	return ret;
}