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
struct stpmic1_wdt {TYPE_1__* pmic; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  WCHDG_CR ; 
 int /*<<< orphan*/  WDT_PING ; 
 int /*<<< orphan*/  WDT_PING_MASK ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct stpmic1_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int pmic_wdt_ping(struct watchdog_device *wdd)
{
	struct stpmic1_wdt *wdt = watchdog_get_drvdata(wdd);

	return regmap_update_bits(wdt->pmic->regmap,
				  WCHDG_CR, WDT_PING_MASK, WDT_PING);
}