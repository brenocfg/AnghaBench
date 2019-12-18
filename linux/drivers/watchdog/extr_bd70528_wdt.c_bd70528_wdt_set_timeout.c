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
struct wdtbd70528 {int /*<<< orphan*/  mfd; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct watchdog_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD70528_MASK_WDT_HOUR ; 
 int /*<<< orphan*/  BD70528_MASK_WDT_MINUTE ; 
 int /*<<< orphan*/  BD70528_MASK_WDT_SEC ; 
 int /*<<< orphan*/  BD70528_REG_WDT_HOUR ; 
 int /*<<< orphan*/  BD70528_REG_WDT_MINUTE ; 
 int /*<<< orphan*/  BD70528_REG_WDT_SEC ; 
 int /*<<< orphan*/  bd70528_wdt_lock (int /*<<< orphan*/ ) ; 
 int bd70528_wdt_set_locked (struct wdtbd70528*,int) ; 
 int /*<<< orphan*/  bd70528_wdt_unlock (int /*<<< orphan*/ ) ; 
 unsigned int bin2bcd (unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct wdtbd70528* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int bd70528_wdt_set_timeout(struct watchdog_device *wdt,
				   unsigned int timeout)
{
	unsigned int hours;
	unsigned int minutes;
	unsigned int seconds;
	int ret;
	struct wdtbd70528 *w = watchdog_get_drvdata(wdt);

	seconds = timeout;
	hours = timeout / (60 * 60);
	/* Maximum timeout is 1h 59m 59s => hours is 1 or 0 */
	if (hours)
		seconds -= (60 * 60);
	minutes = seconds / 60;
	seconds = seconds % 60;

	bd70528_wdt_lock(w->mfd);

	ret = bd70528_wdt_set_locked(w, 0);
	if (ret)
		goto out_unlock;

	ret = regmap_update_bits(w->regmap, BD70528_REG_WDT_HOUR,
				 BD70528_MASK_WDT_HOUR, hours);
	if (ret) {
		dev_err(w->dev, "Failed to set WDT hours\n");
		goto out_en_unlock;
	}
	ret = regmap_update_bits(w->regmap, BD70528_REG_WDT_MINUTE,
				 BD70528_MASK_WDT_MINUTE, bin2bcd(minutes));
	if (ret) {
		dev_err(w->dev, "Failed to set WDT minutes\n");
		goto out_en_unlock;
	}
	ret = regmap_update_bits(w->regmap, BD70528_REG_WDT_SEC,
				 BD70528_MASK_WDT_SEC, bin2bcd(seconds));
	if (ret)
		dev_err(w->dev, "Failed to set WDT seconds\n");
	else
		dev_dbg(w->dev, "WDT tmo set to %u\n", timeout);

out_en_unlock:
	ret = bd70528_wdt_set_locked(w, 1);
out_unlock:
	bd70528_wdt_unlock(w->mfd);

	return ret;
}