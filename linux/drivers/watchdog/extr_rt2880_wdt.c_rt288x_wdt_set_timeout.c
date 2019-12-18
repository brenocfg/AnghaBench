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

/* Variables and functions */
 int /*<<< orphan*/  rt288x_wdt_ping (struct watchdog_device*) ; 

__attribute__((used)) static int rt288x_wdt_set_timeout(struct watchdog_device *w, unsigned int t)
{
	w->timeout = t;
	rt288x_wdt_ping(w);

	return 0;
}