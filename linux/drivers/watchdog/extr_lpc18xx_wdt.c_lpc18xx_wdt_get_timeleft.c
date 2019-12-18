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
struct lpc18xx_wdt_dev {unsigned int clk_rate; scalar_t__ base; } ;

/* Variables and functions */
 unsigned int LPC18XX_WDT_CLK_DIV ; 
 scalar_t__ LPC18XX_WDT_TV ; 
 unsigned int readl (scalar_t__) ; 
 struct lpc18xx_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int lpc18xx_wdt_get_timeleft(struct watchdog_device *wdt_dev)
{
	struct lpc18xx_wdt_dev *lpc18xx_wdt = watchdog_get_drvdata(wdt_dev);
	unsigned int val;

	val = readl(lpc18xx_wdt->base + LPC18XX_WDT_TV);
	return (val * LPC18XX_WDT_CLK_DIV) / lpc18xx_wdt->clk_rate;
}