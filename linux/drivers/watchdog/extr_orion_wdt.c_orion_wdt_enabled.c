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
struct watchdog_device {int dummy; } ;
struct orion_watchdog {TYPE_1__* data; } ;
struct TYPE_2__ {int (* enabled ) (struct orion_watchdog*) ;} ;

/* Variables and functions */
 int stub1 (struct orion_watchdog*) ; 
 struct orion_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int orion_wdt_enabled(struct watchdog_device *wdt_dev)
{
	struct orion_watchdog *dev = watchdog_get_drvdata(wdt_dev);

	return dev->data->enabled(dev);
}