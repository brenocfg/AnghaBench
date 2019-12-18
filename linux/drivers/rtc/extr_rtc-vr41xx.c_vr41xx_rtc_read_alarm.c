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
struct rtc_time {int dummy; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; struct rtc_time time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECMPHREG ; 
 int /*<<< orphan*/  ECMPLREG ; 
 int /*<<< orphan*/  ECMPMREG ; 
 int /*<<< orphan*/  alarm_enabled ; 
 unsigned long rtc1_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,struct rtc_time*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vr41xx_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *wkalrm)
{
	unsigned long low, mid, high;
	struct rtc_time *time = &wkalrm->time;

	spin_lock_irq(&rtc_lock);

	low = rtc1_read(ECMPLREG);
	mid = rtc1_read(ECMPMREG);
	high = rtc1_read(ECMPHREG);
	wkalrm->enabled = alarm_enabled;

	spin_unlock_irq(&rtc_lock);

	rtc_time64_to_tm((high << 17) | (mid << 1) | (low >> 15), time);

	return 0;
}