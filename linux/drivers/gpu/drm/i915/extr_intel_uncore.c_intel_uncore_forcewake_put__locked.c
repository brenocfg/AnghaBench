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
struct intel_uncore {TYPE_1__ funcs; int /*<<< orphan*/  lock; } ;
typedef  enum forcewake_domains { ____Placeholder_forcewake_domains } forcewake_domains ;

/* Variables and functions */
 int /*<<< orphan*/  __intel_uncore_forcewake_put (struct intel_uncore*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void intel_uncore_forcewake_put__locked(struct intel_uncore *uncore,
					enum forcewake_domains fw_domains)
{
	lockdep_assert_held(&uncore->lock);

	if (!uncore->funcs.force_wake_put)
		return;

	__intel_uncore_forcewake_put(uncore, fw_domains);
}