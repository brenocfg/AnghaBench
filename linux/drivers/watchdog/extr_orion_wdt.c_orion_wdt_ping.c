#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {int timeout; int pretimeout; } ;
struct TYPE_5__ {TYPE_3__* info; } ;
struct orion_watchdog {int clk_rate; scalar_t__ reg; TYPE_2__ wdt; TYPE_1__* data; } ;
struct TYPE_6__ {int options; } ;
struct TYPE_4__ {scalar_t__ wdt_counter_offset; } ;

/* Variables and functions */
 scalar_t__ TIMER1_VAL_OFF ; 
 int WDIOF_PRETIMEOUT ; 
 struct orion_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int orion_wdt_ping(struct watchdog_device *wdt_dev)
{
	struct orion_watchdog *dev = watchdog_get_drvdata(wdt_dev);
	/* Reload watchdog duration */
	writel(dev->clk_rate * wdt_dev->timeout,
	       dev->reg + dev->data->wdt_counter_offset);
	if (dev->wdt.info->options & WDIOF_PRETIMEOUT)
		writel(dev->clk_rate * (wdt_dev->timeout - wdt_dev->pretimeout),
		       dev->reg + TIMER1_VAL_OFF);

	return 0;
}