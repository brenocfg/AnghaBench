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
struct gb_svc_watchdog {int enabled; int /*<<< orphan*/  work; } ;
struct gb_svc {struct gb_svc_watchdog* watchdog; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SVC_WATCHDOG_PERIOD ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int gb_svc_watchdog_enable(struct gb_svc *svc)
{
	struct gb_svc_watchdog *watchdog;

	if (!svc->watchdog)
		return -ENODEV;

	watchdog = svc->watchdog;
	if (watchdog->enabled)
		return 0;

	watchdog->enabled = true;
	schedule_delayed_work(&watchdog->work, SVC_WATCHDOG_PERIOD);
	return 0;
}