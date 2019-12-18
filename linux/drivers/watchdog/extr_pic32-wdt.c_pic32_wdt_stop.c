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
struct pic32_wdt {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIC32_CLR (scalar_t__) ; 
 int /*<<< orphan*/  WDTCON_ON ; 
 scalar_t__ WDTCON_REG ; 
 int /*<<< orphan*/  nop () ; 
 struct pic32_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pic32_wdt_stop(struct watchdog_device *wdd)
{
	struct pic32_wdt *wdt = watchdog_get_drvdata(wdd);

	writel(WDTCON_ON, PIC32_CLR(wdt->regs + WDTCON_REG));

	/*
	 * Cannot touch registers in the CPU cycle following clearing the
	 * ON bit.
	 */
	nop();

	return 0;
}