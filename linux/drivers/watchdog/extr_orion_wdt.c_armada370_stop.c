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
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {int dummy; } ;
struct orion_watchdog {TYPE_1__* data; scalar_t__ reg; int /*<<< orphan*/  rstout; } ;
struct TYPE_2__ {int /*<<< orphan*/  wdt_enable_bit; int /*<<< orphan*/  rstout_enable_bit; } ;

/* Variables and functions */
 scalar_t__ TIMER_CTRL ; 
 int /*<<< orphan*/  atomic_io_modify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 struct orion_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada370_stop(struct watchdog_device *wdt_dev)
{
	struct orion_watchdog *dev = watchdog_get_drvdata(wdt_dev);
	u32 reg;

	/* Disable reset on watchdog */
	reg = readl(dev->rstout);
	reg &= ~dev->data->rstout_enable_bit;
	writel(reg, dev->rstout);

	/* Disable watchdog timer */
	atomic_io_modify(dev->reg + TIMER_CTRL, dev->data->wdt_enable_bit, 0);

	return 0;
}