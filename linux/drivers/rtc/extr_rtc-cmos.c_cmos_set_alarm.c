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
struct TYPE_2__ {int tm_mon; unsigned char tm_mday; unsigned char tm_hour; unsigned char tm_min; unsigned char tm_sec; } ;
struct rtc_wkalrm {TYPE_1__ time; scalar_t__ enabled; } ;
struct device {int dummy; } ;
struct cmos_rtc {int /*<<< orphan*/  alarm_expires; scalar_t__ mon_alrm; scalar_t__ day_alrm; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 unsigned char CMOS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMOS_WRITE (unsigned char,scalar_t__) ; 
 int EIO ; 
 int /*<<< orphan*/  RTC_AIE ; 
 scalar_t__ RTC_ALWAYS_BCD ; 
 int /*<<< orphan*/  RTC_CONTROL ; 
 unsigned char RTC_DM_BINARY ; 
 scalar_t__ RTC_HOURS_ALARM ; 
 scalar_t__ RTC_MINUTES_ALARM ; 
 scalar_t__ RTC_SECONDS_ALARM ; 
 int bin2bcd (unsigned char) ; 
 int /*<<< orphan*/  cmos_irq_disable (struct cmos_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmos_irq_enable (struct cmos_rtc*,int /*<<< orphan*/ ) ; 
 int cmos_validate_alarm (struct device*,struct rtc_wkalrm*) ; 
 struct cmos_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hpet_set_alarm_time (unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  is_valid_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ use_hpet_alarm () ; 

__attribute__((used)) static int cmos_set_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct cmos_rtc	*cmos = dev_get_drvdata(dev);
	unsigned char mon, mday, hrs, min, sec, rtc_control;
	int ret;

	/* This not only a rtc_op, but also called directly */
	if (!is_valid_irq(cmos->irq))
		return -EIO;

	ret = cmos_validate_alarm(dev, t);
	if (ret < 0)
		return ret;

	mon = t->time.tm_mon + 1;
	mday = t->time.tm_mday;
	hrs = t->time.tm_hour;
	min = t->time.tm_min;
	sec = t->time.tm_sec;

	rtc_control = CMOS_READ(RTC_CONTROL);
	if (!(rtc_control & RTC_DM_BINARY) || RTC_ALWAYS_BCD) {
		/* Writing 0xff means "don't care" or "match all".  */
		mon = (mon <= 12) ? bin2bcd(mon) : 0xff;
		mday = (mday >= 1 && mday <= 31) ? bin2bcd(mday) : 0xff;
		hrs = (hrs < 24) ? bin2bcd(hrs) : 0xff;
		min = (min < 60) ? bin2bcd(min) : 0xff;
		sec = (sec < 60) ? bin2bcd(sec) : 0xff;
	}

	spin_lock_irq(&rtc_lock);

	/* next rtc irq must not be from previous alarm setting */
	cmos_irq_disable(cmos, RTC_AIE);

	/* update alarm */
	CMOS_WRITE(hrs, RTC_HOURS_ALARM);
	CMOS_WRITE(min, RTC_MINUTES_ALARM);
	CMOS_WRITE(sec, RTC_SECONDS_ALARM);

	/* the system may support an "enhanced" alarm */
	if (cmos->day_alrm) {
		CMOS_WRITE(mday, cmos->day_alrm);
		if (cmos->mon_alrm)
			CMOS_WRITE(mon, cmos->mon_alrm);
	}

	if (use_hpet_alarm()) {
		/*
		 * FIXME the HPET alarm glue currently ignores day_alrm
		 * and mon_alrm ...
		 */
		hpet_set_alarm_time(t->time.tm_hour, t->time.tm_min,
				    t->time.tm_sec);
	}

	if (t->enabled)
		cmos_irq_enable(cmos, RTC_AIE);

	spin_unlock_irq(&rtc_lock);

	cmos->alarm_expires = rtc_tm_to_time64(&t->time);

	return 0;
}