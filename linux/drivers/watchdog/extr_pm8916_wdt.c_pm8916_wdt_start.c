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
struct pm8916_wdt {scalar_t__ baseaddr; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ PON_PMIC_WD_RESET_S2_CTL2 ; 
 int /*<<< orphan*/  S2_RESET_EN_BIT ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pm8916_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int pm8916_wdt_start(struct watchdog_device *wdev)
{
	struct pm8916_wdt *wdt = watchdog_get_drvdata(wdev);

	return regmap_update_bits(wdt->regmap,
				  wdt->baseaddr + PON_PMIC_WD_RESET_S2_CTL2,
				  S2_RESET_EN_BIT, S2_RESET_EN_BIT);
}