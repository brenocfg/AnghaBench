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
struct timespec64 {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 unsigned int CMOS_READ (int /*<<< orphan*/ ) ; 
 scalar_t__ RTC_ALWAYS_BCD ; 
 int /*<<< orphan*/  RTC_CONTROL ; 
 int /*<<< orphan*/  RTC_DAY_OF_MONTH ; 
 int /*<<< orphan*/  RTC_DEC_YEAR ; 
 unsigned int RTC_DM_BINARY ; 
 int /*<<< orphan*/  RTC_HOURS ; 
 int /*<<< orphan*/  RTC_MINUTES ; 
 int /*<<< orphan*/  RTC_MONTH ; 
 int /*<<< orphan*/  RTC_SECONDS ; 
 int /*<<< orphan*/  RTC_YEAR ; 
 unsigned int bcd2bin (unsigned int) ; 
 int /*<<< orphan*/  mktime64 (unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void read_persistent_clock64(struct timespec64 *ts)
{
	unsigned int year, mon, day, hour, min, sec, real_year;
	unsigned long flags;

	spin_lock_irqsave(&rtc_lock, flags);

	do {
		sec = CMOS_READ(RTC_SECONDS);
		min = CMOS_READ(RTC_MINUTES);
		hour = CMOS_READ(RTC_HOURS);
		day = CMOS_READ(RTC_DAY_OF_MONTH);
		mon = CMOS_READ(RTC_MONTH);
		year = CMOS_READ(RTC_YEAR);
		/*
		 * The PROM will reset the year to either '72 or '73.
		 * Therefore we store the real year separately, in one
		 * of unused BBU RAM locations.
		 */
		real_year = CMOS_READ(RTC_DEC_YEAR);
	} while (sec != CMOS_READ(RTC_SECONDS));

	spin_unlock_irqrestore(&rtc_lock, flags);

	if (!(CMOS_READ(RTC_CONTROL) & RTC_DM_BINARY) || RTC_ALWAYS_BCD) {
		sec = bcd2bin(sec);
		min = bcd2bin(min);
		hour = bcd2bin(hour);
		day = bcd2bin(day);
		mon = bcd2bin(mon);
		year = bcd2bin(year);
	}

	year += real_year - 72 + 2000;

	ts->tv_sec = mktime64(year, mon, day, hour, min, sec);
	ts->tv_nsec = 0;
}