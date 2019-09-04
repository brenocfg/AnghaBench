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
typedef  int /*<<< orphan*/  u64 ;
struct pvclock_vcpu_time_info {int dummy; } ;
struct TYPE_2__ {struct pvclock_vcpu_time_info time; } ;

/* Variables and functions */
 TYPE_1__* __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable_notrace () ; 
 int /*<<< orphan*/  preempt_enable_notrace () ; 
 int /*<<< orphan*/  pvclock_clocksource_read (struct pvclock_vcpu_time_info*) ; 
 int /*<<< orphan*/  xen_vcpu ; 

__attribute__((used)) static u64 xen_clocksource_read(void)
{
        struct pvclock_vcpu_time_info *src;
	u64 ret;

	preempt_disable_notrace();
	src = &__this_cpu_read(xen_vcpu)->time;
	ret = pvclock_clocksource_read(src);
	preempt_enable_notrace();
	return ret;
}