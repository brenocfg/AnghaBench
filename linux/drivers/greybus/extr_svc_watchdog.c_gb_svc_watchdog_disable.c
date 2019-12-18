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
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

int gb_svc_watchdog_disable(struct gb_svc *svc)
{
	struct gb_svc_watchdog *watchdog;

	if (!svc->watchdog)
		return -ENODEV;

	watchdog = svc->watchdog;
	if (!watchdog->enabled)
		return 0;

	watchdog->enabled = false;
	cancel_delayed_work_sync(&watchdog->work);
	return 0;
}