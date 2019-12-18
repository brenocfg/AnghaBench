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
struct imx2_wdt_device {int /*<<< orphan*/  regmap; scalar_t__ ext_reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX2_WDT_WCR ; 
 unsigned int IMX2_WDT_WCR_SRS ; 
 unsigned int IMX2_WDT_WCR_WDA ; 
 unsigned int IMX2_WDT_WCR_WDE ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct imx2_wdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int imx2_wdt_restart(struct watchdog_device *wdog, unsigned long action,
			    void *data)
{
	struct imx2_wdt_device *wdev = watchdog_get_drvdata(wdog);
	unsigned int wcr_enable = IMX2_WDT_WCR_WDE;

	/* Use internal reset or external - not both */
	if (wdev->ext_reset)
		wcr_enable |= IMX2_WDT_WCR_SRS; /* do not assert int reset */
	else
		wcr_enable |= IMX2_WDT_WCR_WDA; /* do not assert ext-reset */

	/* Assert SRS signal */
	regmap_write(wdev->regmap, IMX2_WDT_WCR, wcr_enable);
	/*
	 * Due to imx6q errata ERR004346 (WDOG: WDOG SRS bit requires to be
	 * written twice), we add another two writes to ensure there must be at
	 * least two writes happen in the same one 32kHz clock period.  We save
	 * the target check here, since the writes shouldn't be a huge burden
	 * for other platforms.
	 */
	regmap_write(wdev->regmap, IMX2_WDT_WCR, wcr_enable);
	regmap_write(wdev->regmap, IMX2_WDT_WCR, wcr_enable);

	/* wait for reset to assert... */
	mdelay(500);

	return 0;
}