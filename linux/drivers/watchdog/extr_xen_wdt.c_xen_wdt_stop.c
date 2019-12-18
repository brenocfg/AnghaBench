#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ id; scalar_t__ timeout; } ;

/* Variables and functions */
 int HYPERVISOR_sched_op (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SCHEDOP_watchdog ; 
 TYPE_1__ wdt ; 

__attribute__((used)) static int xen_wdt_stop(struct watchdog_device *wdd)
{
	int err = 0;

	wdt.timeout = 0;
	if (wdt.id)
		err = HYPERVISOR_sched_op(SCHEDOP_watchdog, &wdt);
	if (!err)
		wdt.id = 0;

	return err;
}