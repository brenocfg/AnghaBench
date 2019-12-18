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
struct vt8500_rtc {scalar_t__ regbase; } ;
struct TYPE_2__ {int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_mday; } ;
struct rtc_wkalrm {TYPE_1__ time; scalar_t__ enabled; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ALARM_DAY_S ; 
 int ALARM_ENABLE_MASK ; 
 int TIME_HOUR_S ; 
 int TIME_MIN_S ; 
 scalar_t__ VT8500_RTC_AS ; 
 int bin2bcd (int /*<<< orphan*/ ) ; 
 struct vt8500_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int vt8500_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct vt8500_rtc *vt8500_rtc = dev_get_drvdata(dev);

	writel((alrm->enabled ? ALARM_ENABLE_MASK : 0)
		| (bin2bcd(alrm->time.tm_mday) << ALARM_DAY_S)
		| (bin2bcd(alrm->time.tm_hour) << TIME_HOUR_S)
		| (bin2bcd(alrm->time.tm_min) << TIME_MIN_S)
		| (bin2bcd(alrm->time.tm_sec)),
		vt8500_rtc->regbase + VT8500_RTC_AS);

	return 0;
}