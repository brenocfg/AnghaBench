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
struct rtc_wkalrm {unsigned int pending; unsigned int enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;
struct coh901331_port {int /*<<< orphan*/  clk; scalar_t__ virtbase; } ;

/* Variables and functions */
 scalar_t__ COH901331_ALARM ; 
 scalar_t__ COH901331_IRQ_EVENT ; 
 scalar_t__ COH901331_IRQ_MASK ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct coh901331_port* dev_get_drvdata (struct device*) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int coh901331_read_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct coh901331_port *rtap = dev_get_drvdata(dev);

	clk_enable(rtap->clk);
	rtc_time64_to_tm(readl(rtap->virtbase + COH901331_ALARM), &alarm->time);
	alarm->pending = readl(rtap->virtbase + COH901331_IRQ_EVENT) & 1U;
	alarm->enabled = readl(rtap->virtbase + COH901331_IRQ_MASK) & 1U;
	clk_disable(rtap->clk);

	return 0;
}