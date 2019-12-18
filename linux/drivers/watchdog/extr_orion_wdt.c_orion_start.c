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
struct watchdog_device {int timeout; } ;
struct orion_watchdog {int clk_rate; TYPE_1__* data; scalar_t__ rstout; scalar_t__ reg; } ;
struct TYPE_2__ {int /*<<< orphan*/  rstout_enable_bit; int /*<<< orphan*/  wdt_enable_bit; scalar_t__ wdt_counter_offset; } ;

/* Variables and functions */
 scalar_t__ TIMER_CTRL ; 
 int /*<<< orphan*/  atomic_io_modify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct orion_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int orion_start(struct watchdog_device *wdt_dev)
{
	struct orion_watchdog *dev = watchdog_get_drvdata(wdt_dev);

	/* Set watchdog duration */
	writel(dev->clk_rate * wdt_dev->timeout,
	       dev->reg + dev->data->wdt_counter_offset);

	/* Enable watchdog timer */
	atomic_io_modify(dev->reg + TIMER_CTRL, dev->data->wdt_enable_bit,
						dev->data->wdt_enable_bit);

	/* Enable reset on watchdog */
	atomic_io_modify(dev->rstout, dev->data->rstout_enable_bit,
				      dev->data->rstout_enable_bit);

	return 0;
}