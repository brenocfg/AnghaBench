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
struct intel_uncore_forcewake_domain {int mask; int /*<<< orphan*/  timer; int /*<<< orphan*/  wake_count; TYPE_1__* uncore; } ;
struct TYPE_2__ {int fw_domains_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  NSEC_PER_MSEC ; 
 int /*<<< orphan*/  hrtimer_start_range_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
fw_domain_arm_timer(struct intel_uncore_forcewake_domain *d)
{
	GEM_BUG_ON(d->uncore->fw_domains_timer & d->mask);
	d->uncore->fw_domains_timer |= d->mask;
	d->wake_count++;
	hrtimer_start_range_ns(&d->timer,
			       NSEC_PER_MSEC,
			       NSEC_PER_MSEC,
			       HRTIMER_MODE_REL);
}