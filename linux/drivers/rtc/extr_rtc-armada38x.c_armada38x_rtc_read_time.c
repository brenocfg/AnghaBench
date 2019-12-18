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
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct armada38x_rtc {int /*<<< orphan*/  lock; TYPE_1__* data; } ;
struct TYPE_2__ {unsigned long (* read_rtc_reg ) (struct armada38x_rtc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_TIME ; 
 struct armada38x_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,struct rtc_time*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long stub1 (struct armada38x_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int armada38x_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct armada38x_rtc *rtc = dev_get_drvdata(dev);
	unsigned long time, flags;

	spin_lock_irqsave(&rtc->lock, flags);
	time = rtc->data->read_rtc_reg(rtc, RTC_TIME);
	spin_unlock_irqrestore(&rtc->lock, flags);

	rtc_time64_to_tm(time, tm);

	return 0;
}