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
struct rtc_time {int tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_DAY_OF_MONTH ; 
 int /*<<< orphan*/  RTC_HOURS ; 
 int /*<<< orphan*/  RTC_MINUTES ; 
 int /*<<< orphan*/  RTC_MONTH ; 
 int /*<<< orphan*/  RTC_SECONDS ; 
 int /*<<< orphan*/  RTC_YEAR ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 void* vrtc_cmos_read (int /*<<< orphan*/ ) ; 
 scalar_t__ vrtc_is_updating () ; 

__attribute__((used)) static int mrst_read_time(struct device *dev, struct rtc_time *time)
{
	unsigned long flags;

	if (vrtc_is_updating())
		msleep(20);

	spin_lock_irqsave(&rtc_lock, flags);
	time->tm_sec = vrtc_cmos_read(RTC_SECONDS);
	time->tm_min = vrtc_cmos_read(RTC_MINUTES);
	time->tm_hour = vrtc_cmos_read(RTC_HOURS);
	time->tm_mday = vrtc_cmos_read(RTC_DAY_OF_MONTH);
	time->tm_mon = vrtc_cmos_read(RTC_MONTH);
	time->tm_year = vrtc_cmos_read(RTC_YEAR);
	spin_unlock_irqrestore(&rtc_lock, flags);

	/* Adjust for the 1972/1900 */
	time->tm_year += 72;
	time->tm_mon--;
	return 0;
}