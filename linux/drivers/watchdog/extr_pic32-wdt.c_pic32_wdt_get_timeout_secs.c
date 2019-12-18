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
typedef  unsigned long u32 ;
struct pic32_wdt {int /*<<< orphan*/  clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long BIT (unsigned long) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned long,unsigned long,...) ; 
 int /*<<< orphan*/  pic32_wdt_get_clk_id (struct pic32_wdt*) ; 
 unsigned long pic32_wdt_get_post_scaler (struct pic32_wdt*) ; 

__attribute__((used)) static u32 pic32_wdt_get_timeout_secs(struct pic32_wdt *wdt, struct device *dev)
{
	unsigned long rate;
	u32 period, ps, terminal;

	rate = clk_get_rate(wdt->clk);

	dev_dbg(dev, "wdt: clk_id %d, clk_rate %lu (prescale)\n",
		pic32_wdt_get_clk_id(wdt), rate);

	/* default, prescaler of 32 (i.e. div-by-32) is implicit. */
	rate >>= 5;
	if (!rate)
		return 0;

	/* calculate terminal count from postscaler. */
	ps = pic32_wdt_get_post_scaler(wdt);
	terminal = BIT(ps);

	/* find time taken (in secs) to reach terminal count */
	period = terminal / rate;
	dev_dbg(dev,
		"wdt: clk_rate %lu (postscale) / terminal %d, timeout %dsec\n",
		rate, terminal, period);

	return period;
}