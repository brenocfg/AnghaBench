#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;
struct armada38x_rtc {int /*<<< orphan*/  lock; TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unmask_interrupt ) (struct armada38x_rtc*) ;int /*<<< orphan*/  alarm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALARM_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTC_ALARM1 ; 
 int /*<<< orphan*/  RTC_IRQ1_CONF ; 
 unsigned long RTC_IRQ_AL_EN ; 
 struct armada38x_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_delayed_write (unsigned long,struct armada38x_rtc*,int /*<<< orphan*/ ) ; 
 unsigned long rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct armada38x_rtc*) ; 

__attribute__((used)) static int armada38x_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct armada38x_rtc *rtc = dev_get_drvdata(dev);
	u32 reg = ALARM_REG(RTC_ALARM1, rtc->data->alarm);
	u32 reg_irq = ALARM_REG(RTC_IRQ1_CONF, rtc->data->alarm);
	unsigned long time, flags;

	time = rtc_tm_to_time64(&alrm->time);

	spin_lock_irqsave(&rtc->lock, flags);

	rtc_delayed_write(time, rtc, reg);

	if (alrm->enabled) {
		rtc_delayed_write(RTC_IRQ_AL_EN, rtc, reg_irq);
		rtc->data->unmask_interrupt(rtc);
	}

	spin_unlock_irqrestore(&rtc->lock, flags);

	return 0;
}