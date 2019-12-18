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
struct intel_uncore {int /*<<< orphan*/  lock; TYPE_1__* debug; int /*<<< orphan*/  user_forcewake_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FORCEWAKE_ALL ; 
 int /*<<< orphan*/  intel_uncore_forcewake_get__locked (struct intel_uncore*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmio_debug_suspend (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void intel_uncore_forcewake_user_get(struct intel_uncore *uncore)
{
	spin_lock_irq(&uncore->lock);
	if (!uncore->user_forcewake_count++) {
		intel_uncore_forcewake_get__locked(uncore, FORCEWAKE_ALL);
		spin_lock(&uncore->debug->lock);
		mmio_debug_suspend(uncore->debug);
		spin_unlock(&uncore->debug->lock);
	}
	spin_unlock_irq(&uncore->lock);
}