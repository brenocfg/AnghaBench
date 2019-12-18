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
struct mc13xxx_rtc {int /*<<< orphan*/  rtc; struct mc13xxx* mc13xxx; } ;
struct mc13xxx {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 int /*<<< orphan*/  mc13xxx_irq_ack (struct mc13xxx*,int) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t mc13xxx_rtc_alarm_handler(int irq, void *dev)
{
	struct mc13xxx_rtc *priv = dev;
	struct mc13xxx *mc13xxx = priv->mc13xxx;

	rtc_update_irq(priv->rtc, 1, RTC_IRQF | RTC_AF);

	mc13xxx_irq_ack(mc13xxx, irq);

	return IRQ_HANDLED;
}