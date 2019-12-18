#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct intel_uncore {int /*<<< orphan*/  lock; TYPE_3__* debug; TYPE_1__* i915; int /*<<< orphan*/  user_forcewake_count; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_2__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 scalar_t__ check_for_unclaimed_mmio (struct intel_uncore*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  intel_uncore_forcewake_put__locked (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmio_debug_resume (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void intel_uncore_forcewake_user_put(struct intel_uncore *uncore)
{
	spin_lock_irq(&uncore->lock);
	if (!--uncore->user_forcewake_count) {
		spin_lock(&uncore->debug->lock);
		mmio_debug_resume(uncore->debug);

		if (check_for_unclaimed_mmio(uncore))
			dev_info(uncore->i915->drm.dev,
				 "Invalid mmio detected during user access\n");
		spin_unlock(&uncore->debug->lock);

		intel_uncore_forcewake_put__locked(uncore, FORCEWAKE_ALL);
	}
	spin_unlock_irq(&uncore->lock);
}