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
struct watchdog_device {int dummy; } ;
struct bcm2835_wdt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bcm2835_restart (struct bcm2835_wdt*) ; 
 struct bcm2835_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int bcm2835_restart(struct watchdog_device *wdog,
			   unsigned long action, void *data)
{
	struct bcm2835_wdt *wdt = watchdog_get_drvdata(wdog);

	__bcm2835_restart(wdt);

	return 0;
}