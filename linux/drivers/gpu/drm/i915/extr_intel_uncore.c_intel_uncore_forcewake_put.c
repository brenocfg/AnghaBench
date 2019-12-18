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
struct TYPE_2__ {int /*<<< orphan*/  force_wake_put; } ;
struct intel_uncore {int /*<<< orphan*/  lock; TYPE_1__ funcs; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_uncore_forcewake_put (struct intel_uncore*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void intel_uncore_forcewake_put(struct intel_uncore *uncore,
				enum forcewake_domains fw_domains)
{
	unsigned long irqflags;

	if (!uncore->funcs.force_wake_put)
		return;

	spin_lock_irqsave(&uncore->lock, irqflags);
	__intel_uncore_forcewake_put(uncore, fw_domains);
	spin_unlock_irqrestore(&uncore->lock, irqflags);
}