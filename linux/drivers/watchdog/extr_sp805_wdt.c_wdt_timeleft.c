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
typedef  int u64 ;
struct watchdog_device {int dummy; } ;
struct sp805_wdt {int /*<<< orphan*/  rate; int /*<<< orphan*/  lock; scalar_t__ load_val; scalar_t__ base; } ;

/* Variables and functions */
 int INT_MASK ; 
 scalar_t__ WDTRIS ; 
 scalar_t__ WDTVALUE ; 
 unsigned int div_u64 (int,int /*<<< orphan*/ ) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct sp805_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int wdt_timeleft(struct watchdog_device *wdd)
{
	struct sp805_wdt *wdt = watchdog_get_drvdata(wdd);
	u64 load;

	spin_lock(&wdt->lock);
	load = readl_relaxed(wdt->base + WDTVALUE);

	/*If the interrupt is inactive then time left is WDTValue + WDTLoad. */
	if (!(readl_relaxed(wdt->base + WDTRIS) & INT_MASK))
		load += wdt->load_val + 1;
	spin_unlock(&wdt->lock);

	return div_u64(load, wdt->rate);
}