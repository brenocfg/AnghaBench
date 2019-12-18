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

/* Variables and functions */
 int nov2dec_transitions (struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (scalar_t__,struct rtc_time*) ; 
 scalar_t__ rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static void rockchip_to_gregorian(struct rtc_time *tm)
{
	/* If it's Nov 31st, rtc_tm_to_time64() will count that like Dec 1st */
	time64_t time = rtc_tm_to_time64(tm);
	rtc_time64_to_tm(time + nov2dec_transitions(tm) * 86400, tm);
}