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
struct cpuidle_driver {TYPE_1__* states; } ;
struct cpuidle_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned long flg2MWAIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwait_idle_with_hints (unsigned long,unsigned long) ; 

__attribute__((used)) static void intel_idle_s2idle(struct cpuidle_device *dev,
			     struct cpuidle_driver *drv, int index)
{
	unsigned long ecx = 1; /* break on interrupt flag */
	unsigned long eax = flg2MWAIT(drv->states[index].flags);

	mwait_idle_with_hints(eax, ecx);
}