#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {TYPE_1__* info; } ;
struct orion_watchdog {scalar_t__ reg; TYPE_2__* data; int /*<<< orphan*/  rstout; scalar_t__ rstout_mask; } ;
struct TYPE_4__ {int /*<<< orphan*/  wdt_enable_bit; int /*<<< orphan*/  rstout_enable_bit; int /*<<< orphan*/  rstout_mask_bit; } ;
struct TYPE_3__ {int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMER1_ENABLE_BIT ; 
 scalar_t__ TIMER_CTRL ; 
 int WDIOF_PRETIMEOUT ; 
 int /*<<< orphan*/  atomic_io_modify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 struct orion_watchdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada375_stop(struct watchdog_device *wdt_dev)
{
	struct orion_watchdog *dev = watchdog_get_drvdata(wdt_dev);
	u32 reg, mask;

	/* Disable reset on watchdog */
	atomic_io_modify(dev->rstout_mask, dev->data->rstout_mask_bit,
					   dev->data->rstout_mask_bit);
	reg = readl(dev->rstout);
	reg &= ~dev->data->rstout_enable_bit;
	writel(reg, dev->rstout);

	/* Disable watchdog timer */
	mask = dev->data->wdt_enable_bit;
	if (wdt_dev->info->options & WDIOF_PRETIMEOUT)
		mask |= TIMER1_ENABLE_BIT;
	atomic_io_modify(dev->reg + TIMER_CTRL, mask, 0);

	return 0;
}