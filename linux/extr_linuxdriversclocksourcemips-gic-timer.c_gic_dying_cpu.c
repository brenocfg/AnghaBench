#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  gic_clockevent_cpu_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gic_clockevent_device ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gic_dying_cpu(unsigned int cpu)
{
	gic_clockevent_cpu_exit(this_cpu_ptr(&gic_clockevent_device));
	return 0;
}