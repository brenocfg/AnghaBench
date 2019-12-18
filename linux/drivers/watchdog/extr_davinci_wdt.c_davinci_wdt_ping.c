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
struct davinci_wdt_device {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDKEY_SEQ0 ; 
 int /*<<< orphan*/  WDKEY_SEQ1 ; 
 scalar_t__ WDTCR ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct davinci_wdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int davinci_wdt_ping(struct watchdog_device *wdd)
{
	struct davinci_wdt_device *davinci_wdt = watchdog_get_drvdata(wdd);

	/* put watchdog in service state */
	iowrite32(WDKEY_SEQ0, davinci_wdt->base + WDTCR);
	/* put watchdog in active state */
	iowrite32(WDKEY_SEQ1, davinci_wdt->base + WDTCR);
	return 0;
}