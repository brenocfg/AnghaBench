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
struct watchdog_device {unsigned int timeout; } ;
struct ts72xx_wdt_priv {int /*<<< orphan*/  regval; } ;

/* Variables and functions */
 int /*<<< orphan*/  TS72XX_WDT_CTRL_1SEC ; 
 int /*<<< orphan*/  TS72XX_WDT_CTRL_2SEC ; 
 int /*<<< orphan*/  TS72XX_WDT_CTRL_4SEC ; 
 int /*<<< orphan*/  TS72XX_WDT_CTRL_8SEC ; 
 int /*<<< orphan*/  ts72xx_wdt_start (struct watchdog_device*) ; 
 int /*<<< orphan*/  ts72xx_wdt_stop (struct watchdog_device*) ; 
 scalar_t__ watchdog_active (struct watchdog_device*) ; 
 struct ts72xx_wdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int ts72xx_wdt_settimeout(struct watchdog_device *wdd, unsigned int to)
{
	struct ts72xx_wdt_priv *priv = watchdog_get_drvdata(wdd);

	if (to == 1) {
		priv->regval = TS72XX_WDT_CTRL_1SEC;
	} else if (to == 2) {
		priv->regval = TS72XX_WDT_CTRL_2SEC;
	} else if (to <= 4) {
		priv->regval = TS72XX_WDT_CTRL_4SEC;
		to = 4;
	} else {
		priv->regval = TS72XX_WDT_CTRL_8SEC;
		if (to <= 8)
			to = 8;
	}

	wdd->timeout = to;

	if (watchdog_active(wdd)) {
		ts72xx_wdt_stop(wdd);
		ts72xx_wdt_start(wdd);
	}

	return 0;
}