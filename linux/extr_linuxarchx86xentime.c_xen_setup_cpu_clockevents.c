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
struct TYPE_2__ {int /*<<< orphan*/  evt; } ;

/* Variables and functions */
 int /*<<< orphan*/  clockevents_register_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ xen_clock_events ; 

void xen_setup_cpu_clockevents(void)
{
	clockevents_register_device(this_cpu_ptr(&xen_clock_events.evt));
}