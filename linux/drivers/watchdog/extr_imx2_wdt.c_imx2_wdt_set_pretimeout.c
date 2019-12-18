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
struct watchdog_device {unsigned int pretimeout; } ;
struct imx2_wdt_device {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int IMX2_WDT_MAX_TIME ; 
 int /*<<< orphan*/  IMX2_WDT_WICR ; 
 unsigned int IMX2_WDT_WICR_WICT ; 
 unsigned int IMX2_WDT_WICR_WIE ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct imx2_wdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int imx2_wdt_set_pretimeout(struct watchdog_device *wdog,
				   unsigned int new_pretimeout)
{
	struct imx2_wdt_device *wdev = watchdog_get_drvdata(wdog);

	if (new_pretimeout >= IMX2_WDT_MAX_TIME)
		return -EINVAL;

	wdog->pretimeout = new_pretimeout;

	regmap_update_bits(wdev->regmap, IMX2_WDT_WICR,
			   IMX2_WDT_WICR_WIE | IMX2_WDT_WICR_WICT,
			   IMX2_WDT_WICR_WIE | (new_pretimeout << 1));
	return 0;
}