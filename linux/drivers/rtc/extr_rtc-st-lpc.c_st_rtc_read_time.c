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
struct st_rtc {int /*<<< orphan*/  clkrate; int /*<<< orphan*/  lock; scalar_t__ ioaddr; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ LPC_LPT_LSB_OFF ; 
 scalar_t__ LPC_LPT_MSB_OFF ; 
 struct st_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  do_div (unsigned long long,int /*<<< orphan*/ ) ; 
 unsigned long readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long long,struct rtc_time*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int st_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct st_rtc *rtc = dev_get_drvdata(dev);
	unsigned long lpt_lsb, lpt_msb;
	unsigned long long lpt;
	unsigned long flags;

	spin_lock_irqsave(&rtc->lock, flags);

	do {
		lpt_msb = readl_relaxed(rtc->ioaddr + LPC_LPT_MSB_OFF);
		lpt_lsb = readl_relaxed(rtc->ioaddr + LPC_LPT_LSB_OFF);
	} while (readl_relaxed(rtc->ioaddr + LPC_LPT_MSB_OFF) != lpt_msb);

	spin_unlock_irqrestore(&rtc->lock, flags);

	lpt = ((unsigned long long)lpt_msb << 32) | lpt_lsb;
	do_div(lpt, rtc->clkrate);
	rtc_time64_to_tm(lpt, tm);

	return 0;
}