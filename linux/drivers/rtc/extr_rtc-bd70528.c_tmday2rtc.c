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
struct rtc_time {int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct bd70528_rtc_day {int /*<<< orphan*/  hour; int /*<<< orphan*/  min; int /*<<< orphan*/  sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD70528_MASK_RTC_HOUR ; 
 int /*<<< orphan*/  BD70528_MASK_RTC_MINUTE ; 
 int /*<<< orphan*/  BD70528_MASK_RTC_SEC ; 
 int /*<<< orphan*/  bin2bcd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void tmday2rtc(struct rtc_time *t, struct bd70528_rtc_day *d)
{
	d->sec &= ~BD70528_MASK_RTC_SEC;
	d->min &= ~BD70528_MASK_RTC_MINUTE;
	d->hour &= ~BD70528_MASK_RTC_HOUR;
	d->sec |= bin2bcd(t->tm_sec);
	d->min |= bin2bcd(t->tm_min);
	d->hour |= bin2bcd(t->tm_hour);
}