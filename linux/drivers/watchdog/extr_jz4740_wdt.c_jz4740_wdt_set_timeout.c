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
typedef  unsigned short u16 ;
struct watchdog_device {unsigned int timeout; } ;
struct jz4740_wdt_drvdata {scalar_t__ base; int /*<<< orphan*/  rtc_clk; } ;

/* Variables and functions */
 unsigned short JZ_WDT_CLOCK_DIV_1 ; 
 unsigned short JZ_WDT_CLOCK_DIV_1024 ; 
 unsigned short JZ_WDT_CLOCK_RTC ; 
 scalar_t__ TCU_REG_WDT_TCER ; 
 scalar_t__ TCU_REG_WDT_TCNT ; 
 scalar_t__ TCU_REG_WDT_TCSR ; 
 scalar_t__ TCU_REG_WDT_TDR ; 
 int TCU_TCSR_PRESCALE_LSB ; 
 int TCU_WDT_TCER_TCEN ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int readb (scalar_t__) ; 
 struct jz4740_wdt_drvdata* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (unsigned short,scalar_t__) ; 

__attribute__((used)) static int jz4740_wdt_set_timeout(struct watchdog_device *wdt_dev,
				    unsigned int new_timeout)
{
	struct jz4740_wdt_drvdata *drvdata = watchdog_get_drvdata(wdt_dev);
	unsigned int rtc_clk_rate;
	unsigned int timeout_value;
	unsigned short clock_div = JZ_WDT_CLOCK_DIV_1;
	u8 tcer;

	rtc_clk_rate = clk_get_rate(drvdata->rtc_clk);

	timeout_value = rtc_clk_rate * new_timeout;
	while (timeout_value > 0xffff) {
		if (clock_div == JZ_WDT_CLOCK_DIV_1024) {
			/* Requested timeout too high;
			* use highest possible value. */
			timeout_value = 0xffff;
			break;
		}
		timeout_value >>= 2;
		clock_div += (1 << TCU_TCSR_PRESCALE_LSB);
	}

	tcer = readb(drvdata->base + TCU_REG_WDT_TCER);
	writeb(0x0, drvdata->base + TCU_REG_WDT_TCER);
	writew(clock_div, drvdata->base + TCU_REG_WDT_TCSR);

	writew((u16)timeout_value, drvdata->base + TCU_REG_WDT_TDR);
	writew(0x0, drvdata->base + TCU_REG_WDT_TCNT);
	writew(clock_div | JZ_WDT_CLOCK_RTC, drvdata->base + TCU_REG_WDT_TCSR);

	if (tcer & TCU_WDT_TCER_TCEN)
		writeb(TCU_WDT_TCER_TCEN, drvdata->base + TCU_REG_WDT_TCER);

	wdt_dev->timeout = new_timeout;
	return 0;
}