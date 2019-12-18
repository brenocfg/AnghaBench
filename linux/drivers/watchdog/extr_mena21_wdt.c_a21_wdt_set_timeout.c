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
struct watchdog_device {int timeout; int /*<<< orphan*/  parent; } ;
struct a21_wdt_drv {int /*<<< orphan*/ * gpios; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t GPIO_WD_FAST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 struct a21_wdt_drv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int a21_wdt_set_timeout(struct watchdog_device *wdt,
			       unsigned int timeout)
{
	struct a21_wdt_drv *drv = watchdog_get_drvdata(wdt);

	if (timeout != 1 && timeout != 30) {
		dev_err(wdt->parent, "Only 1 and 30 allowed as timeout\n");
		return -EINVAL;
	}

	if (timeout == 30 && wdt->timeout == 1) {
		dev_err(wdt->parent,
			"Transition from fast to slow mode not allowed\n");
		return -EINVAL;
	}

	if (timeout == 1)
		gpiod_set_value(drv->gpios[GPIO_WD_FAST], 1);
	else
		gpiod_set_value(drv->gpios[GPIO_WD_FAST], 0);

	wdt->timeout = timeout;

	return 0;
}