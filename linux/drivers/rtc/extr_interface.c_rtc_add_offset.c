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
typedef  scalar_t__ time64_t ;
struct rtc_time {int dummy; } ;
struct rtc_device {scalar_t__ offset_secs; scalar_t__ start_secs; scalar_t__ range_min; scalar_t__ range_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtc_time64_to_tm (scalar_t__,struct rtc_time*) ; 
 scalar_t__ rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static void rtc_add_offset(struct rtc_device *rtc, struct rtc_time *tm)
{
	time64_t secs;

	if (!rtc->offset_secs)
		return;

	secs = rtc_tm_to_time64(tm);

	/*
	 * Since the reading time values from RTC device are always in the RTC
	 * original valid range, but we need to skip the overlapped region
	 * between expanded range and original range, which is no need to add
	 * the offset.
	 */
	if ((rtc->start_secs > rtc->range_min && secs >= rtc->start_secs) ||
	    (rtc->start_secs < rtc->range_min &&
	     secs <= (rtc->start_secs + rtc->range_max - rtc->range_min)))
		return;

	rtc_time64_to_tm(secs + rtc->offset_secs, tm);
}