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
typedef  int /*<<< orphan*/  time64_t ;
struct watchdog_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ id; } ;

/* Variables and functions */
 int ENXIO ; 
 int HYPERVISOR_sched_op (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SCHEDOP_watchdog ; 
 int /*<<< orphan*/  set_timeout (struct watchdog_device*) ; 
 TYPE_1__ wdt ; 
 int /*<<< orphan*/  wdt_expires ; 

__attribute__((used)) static int xen_wdt_kick(struct watchdog_device *wdd)
{
	time64_t expires;
	int err;

	expires = set_timeout(wdd);
	if (wdt.id)
		err = HYPERVISOR_sched_op(SCHEDOP_watchdog, &wdt);
	else
		err = -ENXIO;
	if (!err)
		wdt_expires = expires;

	return err;
}