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
struct a21_wdt_drv {int /*<<< orphan*/ * gpios; } ;

/* Variables and functions */
 size_t GPIO_WD_TRIG ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 struct a21_wdt_drv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int a21_wdt_ping(struct watchdog_device *wdt)
{
	struct a21_wdt_drv *drv = watchdog_get_drvdata(wdt);

	gpiod_set_value(drv->gpios[GPIO_WD_TRIG], 0);
	ndelay(10);
	gpiod_set_value(drv->gpios[GPIO_WD_TRIG], 1);

	return 0;
}