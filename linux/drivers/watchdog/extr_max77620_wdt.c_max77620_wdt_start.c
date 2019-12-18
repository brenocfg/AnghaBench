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
struct max77620_wdt {int /*<<< orphan*/  rmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX77620_REG_CNFGGLBL2 ; 
 int /*<<< orphan*/  MAX77620_WDTEN ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct max77620_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int max77620_wdt_start(struct watchdog_device *wdt_dev)
{
	struct max77620_wdt *wdt = watchdog_get_drvdata(wdt_dev);

	return regmap_update_bits(wdt->rmap, MAX77620_REG_CNFGGLBL2,
				  MAX77620_WDTEN, MAX77620_WDTEN);
}