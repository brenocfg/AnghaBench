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
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {int dummy; } ;
struct sp5100_tco {int /*<<< orphan*/  tcobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  SP5100_WDT_CONTROL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SP5100_WDT_START_STOP_BIT ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 struct sp5100_tco* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tco_timer_start(struct watchdog_device *wdd)
{
	struct sp5100_tco *tco = watchdog_get_drvdata(wdd);
	u32 val;

	val = readl(SP5100_WDT_CONTROL(tco->tcobase));
	val |= SP5100_WDT_START_STOP_BIT;
	writel(val, SP5100_WDT_CONTROL(tco->tcobase));

	return 0;
}