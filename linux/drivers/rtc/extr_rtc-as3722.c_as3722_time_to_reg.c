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
typedef  int /*<<< orphan*/  u8 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; } ;

/* Variables and functions */
 int AS3722_RTC_START_YEAR ; 
 int /*<<< orphan*/  bin2bcd (int) ; 

__attribute__((used)) static void as3722_time_to_reg(u8 *rbuff, struct rtc_time *tm)
{
	rbuff[0] = bin2bcd(tm->tm_sec);
	rbuff[1] = bin2bcd(tm->tm_min);
	rbuff[2] = bin2bcd(tm->tm_hour);
	rbuff[3] = bin2bcd(tm->tm_mday);
	rbuff[4] = bin2bcd(tm->tm_mon + 1);
	rbuff[5] = bin2bcd(tm->tm_year - (AS3722_RTC_START_YEAR - 1900));
}