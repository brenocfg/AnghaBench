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
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct imx2_wdt_device {int /*<<< orphan*/  regmap; int /*<<< orphan*/  ext_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX2_WDT_WCR ; 
 int /*<<< orphan*/  IMX2_WDT_WCR_WDE ; 
 int /*<<< orphan*/  IMX2_WDT_WCR_WDZST ; 
 int /*<<< orphan*/  IMX2_WDT_WCR_WRE ; 
 int /*<<< orphan*/  IMX2_WDT_WCR_WT ; 
 int /*<<< orphan*/  WDOG_SEC_TO_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx2_wdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static inline void imx2_wdt_setup(struct watchdog_device *wdog)
{
	struct imx2_wdt_device *wdev = watchdog_get_drvdata(wdog);
	u32 val;

	regmap_read(wdev->regmap, IMX2_WDT_WCR, &val);

	/* Suspend timer in low power mode, write once-only */
	val |= IMX2_WDT_WCR_WDZST;
	/* Strip the old watchdog Time-Out value */
	val &= ~IMX2_WDT_WCR_WT;
	/* Generate internal chip-level reset if WDOG times out */
	if (!wdev->ext_reset)
		val &= ~IMX2_WDT_WCR_WRE;
	/* Or if external-reset assert WDOG_B reset only on time-out */
	else
		val |= IMX2_WDT_WCR_WRE;
	/* Keep Watchdog Disabled */
	val &= ~IMX2_WDT_WCR_WDE;
	/* Set the watchdog's Time-Out value */
	val |= WDOG_SEC_TO_COUNT(wdog->timeout);

	regmap_write(wdev->regmap, IMX2_WDT_WCR, val);

	/* enable the watchdog */
	val |= IMX2_WDT_WCR_WDE;
	regmap_write(wdev->regmap, IMX2_WDT_WCR, val);
}