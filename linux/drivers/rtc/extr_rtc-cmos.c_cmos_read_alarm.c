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
struct TYPE_2__ {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; } ;
struct rtc_wkalrm {int enabled; scalar_t__ pending; TYPE_1__ time; } ;
struct device {int dummy; } ;
struct cmos_rtc {scalar_t__ mon_alrm; scalar_t__ day_alrm; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int CMOS_READ (scalar_t__) ; 
 int EIO ; 
 unsigned char RTC_AIE ; 
 scalar_t__ RTC_ALWAYS_BCD ; 
 scalar_t__ RTC_CONTROL ; 
 unsigned char RTC_DM_BINARY ; 
 scalar_t__ RTC_HOURS_ALARM ; 
 scalar_t__ RTC_MINUTES_ALARM ; 
 scalar_t__ RTC_SECONDS_ALARM ; 
 int bcd2bin (int) ; 
 struct cmos_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  is_valid_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cmos_read_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct cmos_rtc	*cmos = dev_get_drvdata(dev);
	unsigned char	rtc_control;

	/* This not only a rtc_op, but also called directly */
	if (!is_valid_irq(cmos->irq))
		return -EIO;

	/* Basic alarms only support hour, minute, and seconds fields.
	 * Some also support day and month, for alarms up to a year in
	 * the future.
	 */

	spin_lock_irq(&rtc_lock);
	t->time.tm_sec = CMOS_READ(RTC_SECONDS_ALARM);
	t->time.tm_min = CMOS_READ(RTC_MINUTES_ALARM);
	t->time.tm_hour = CMOS_READ(RTC_HOURS_ALARM);

	if (cmos->day_alrm) {
		/* ignore upper bits on readback per ACPI spec */
		t->time.tm_mday = CMOS_READ(cmos->day_alrm) & 0x3f;
		if (!t->time.tm_mday)
			t->time.tm_mday = -1;

		if (cmos->mon_alrm) {
			t->time.tm_mon = CMOS_READ(cmos->mon_alrm);
			if (!t->time.tm_mon)
				t->time.tm_mon = -1;
		}
	}

	rtc_control = CMOS_READ(RTC_CONTROL);
	spin_unlock_irq(&rtc_lock);

	if (!(rtc_control & RTC_DM_BINARY) || RTC_ALWAYS_BCD) {
		if (((unsigned)t->time.tm_sec) < 0x60)
			t->time.tm_sec = bcd2bin(t->time.tm_sec);
		else
			t->time.tm_sec = -1;
		if (((unsigned)t->time.tm_min) < 0x60)
			t->time.tm_min = bcd2bin(t->time.tm_min);
		else
			t->time.tm_min = -1;
		if (((unsigned)t->time.tm_hour) < 0x24)
			t->time.tm_hour = bcd2bin(t->time.tm_hour);
		else
			t->time.tm_hour = -1;

		if (cmos->day_alrm) {
			if (((unsigned)t->time.tm_mday) <= 0x31)
				t->time.tm_mday = bcd2bin(t->time.tm_mday);
			else
				t->time.tm_mday = -1;

			if (cmos->mon_alrm) {
				if (((unsigned)t->time.tm_mon) <= 0x12)
					t->time.tm_mon = bcd2bin(t->time.tm_mon)-1;
				else
					t->time.tm_mon = -1;
			}
		}
	}

	t->enabled = !!(rtc_control & RTC_AIE);
	t->pending = 0;

	return 0;
}