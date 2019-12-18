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
struct imx2_wdt_device {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX2_WDT_WCR ; 
 int /*<<< orphan*/  IMX2_WDT_WCR_WT ; 
 int /*<<< orphan*/  WDOG_SEC_TO_COUNT (unsigned int) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx2_wdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static void __imx2_wdt_set_timeout(struct watchdog_device *wdog,
				   unsigned int new_timeout)
{
	struct imx2_wdt_device *wdev = watchdog_get_drvdata(wdog);

	regmap_update_bits(wdev->regmap, IMX2_WDT_WCR, IMX2_WDT_WCR_WT,
			   WDOG_SEC_TO_COUNT(new_timeout));
}