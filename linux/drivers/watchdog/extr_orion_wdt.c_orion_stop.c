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
struct orion_watchdog {TYPE_1__* data; scalar_t__ reg; scalar_t__ rstout; } ;
struct TYPE_2__ {int /*<<< orphan*/  wdt_enable_bit; int /*<<< orphan*/  rstout_enable_bit; } ;

/* Variables and functions */
 scalar_t__ TIMER_CTRL ; 
 int /*<<< orphan*/  atomic_io_modify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct orion_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int orion_stop(struct watchdog_device *wdt_dev)
{
	struct orion_watchdog *dev = watchdog_get_drvdata(wdt_dev);

	/* Disable reset on watchdog */
	atomic_io_modify(dev->rstout, dev->data->rstout_enable_bit, 0);

	/* Disable watchdog timer */
	atomic_io_modify(dev->reg + TIMER_CTRL, dev->data->wdt_enable_bit, 0);

	return 0;
}