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
typedef  int u8 ;
struct watchdog_device {int /*<<< orphan*/  timeout; } ;
struct jz4740_wdt_drvdata {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TCU_REG_WDT_TCER ; 
 int TCU_WDT_TCER_TCEN ; 
 int /*<<< orphan*/  jz4740_timer_enable_watchdog () ; 
 int /*<<< orphan*/  jz4740_wdt_set_timeout (struct watchdog_device*,int /*<<< orphan*/ ) ; 
 int readb (scalar_t__) ; 
 struct jz4740_wdt_drvdata* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int jz4740_wdt_start(struct watchdog_device *wdt_dev)
{
	struct jz4740_wdt_drvdata *drvdata = watchdog_get_drvdata(wdt_dev);
	u8 tcer;

	tcer = readb(drvdata->base + TCU_REG_WDT_TCER);

	jz4740_timer_enable_watchdog();
	jz4740_wdt_set_timeout(wdt_dev, wdt_dev->timeout);

	/* Start watchdog if it wasn't started already */
	if (!(tcer & TCU_WDT_TCER_TCEN))
		writeb(TCU_WDT_TCER_TCEN, drvdata->base + TCU_REG_WDT_TCER);

	return 0;
}