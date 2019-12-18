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
typedef  int u32 ;
struct sam9_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int AT91_RTT_ALMIEN ; 
 int /*<<< orphan*/  MR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,int) ; 
 struct sam9_rtc* dev_get_drvdata (struct device*) ; 
 int rtt_readl (struct sam9_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtt_writel (struct sam9_rtc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int at91_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct sam9_rtc *rtc = dev_get_drvdata(dev);
	u32 mr = rtt_readl(rtc, MR);

	dev_dbg(dev, "alarm_irq_enable: enabled=%08x, mr %08x\n", enabled, mr);
	if (enabled)
		rtt_writel(rtc, MR, mr | AT91_RTT_ALMIEN);
	else
		rtt_writel(rtc, MR, mr & ~AT91_RTT_ALMIEN);
	return 0;
}