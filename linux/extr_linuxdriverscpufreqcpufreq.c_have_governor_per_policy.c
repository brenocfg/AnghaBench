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
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int CPUFREQ_HAVE_GOVERNOR_PER_POLICY ; 
 TYPE_1__* cpufreq_driver ; 

bool have_governor_per_policy(void)
{
	return !!(cpufreq_driver->flags & CPUFREQ_HAVE_GOVERNOR_PER_POLICY);
}