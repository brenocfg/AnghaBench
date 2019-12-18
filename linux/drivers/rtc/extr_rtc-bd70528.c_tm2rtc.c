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
struct rtc_time {scalar_t__ tm_year; scalar_t__ tm_mon; scalar_t__ tm_wday; scalar_t__ tm_mday; } ;
struct TYPE_2__ {int hour; } ;
struct bd70528_rtc_data {int /*<<< orphan*/  year; int /*<<< orphan*/  month; int /*<<< orphan*/  week; int /*<<< orphan*/  day; TYPE_1__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD70528_MASK_RTC_DAY ; 
 int BD70528_MASK_RTC_HOUR_24H ; 
 int BD70528_MASK_RTC_HOUR_PM ; 
 int /*<<< orphan*/  BD70528_MASK_RTC_MONTH ; 
 int /*<<< orphan*/  BD70528_MASK_RTC_WEEK ; 
 int /*<<< orphan*/  bin2bcd (scalar_t__) ; 
 int /*<<< orphan*/  tmday2rtc (struct rtc_time*,TYPE_1__*) ; 

__attribute__((used)) static inline void tm2rtc(struct rtc_time *t, struct bd70528_rtc_data *r)
{
	r->day &= ~BD70528_MASK_RTC_DAY;
	r->week &= ~BD70528_MASK_RTC_WEEK;
	r->month &= ~BD70528_MASK_RTC_MONTH;
	/*
	 * PM and 24H bits are not used by Wake - thus we clear them
	 * here and not in tmday2rtc() which is also used by wake.
	 */
	r->time.hour &= ~(BD70528_MASK_RTC_HOUR_PM | BD70528_MASK_RTC_HOUR_24H);

	tmday2rtc(t, &r->time);
	/*
	 * We do always set time in 24H mode.
	 */
	r->time.hour |= BD70528_MASK_RTC_HOUR_24H;
	r->day |= bin2bcd(t->tm_mday);
	r->week |= bin2bcd(t->tm_wday);
	r->month |= bin2bcd(t->tm_mon + 1);
	r->year = bin2bcd(t->tm_year - 100);
}