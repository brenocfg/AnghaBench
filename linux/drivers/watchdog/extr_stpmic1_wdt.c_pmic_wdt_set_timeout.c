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
struct watchdog_device {unsigned int timeout; } ;
struct stpmic1_wdt {TYPE_1__* pmic; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCHDG_TIMER_CR ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct stpmic1_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int pmic_wdt_set_timeout(struct watchdog_device *wdd,
				unsigned int timeout)
{
	struct stpmic1_wdt *wdt = watchdog_get_drvdata(wdd);

	wdd->timeout = timeout;
	/* timeout is equal to register value + 1 */
	return regmap_write(wdt->pmic->regmap, WCHDG_TIMER_CR, timeout - 1);
}