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
struct watchdog_device {unsigned int timeout; } ;
struct st_wdog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  st_wdog_load_timer (struct st_wdog*,unsigned int) ; 
 struct st_wdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int st_wdog_set_timeout(struct watchdog_device *wdd,
			       unsigned int timeout)
{
	struct st_wdog *st_wdog = watchdog_get_drvdata(wdd);

	wdd->timeout = timeout;
	st_wdog_load_timer(st_wdog, timeout);

	return 0;
}