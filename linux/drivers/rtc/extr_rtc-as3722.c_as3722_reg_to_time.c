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
typedef  int u8 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; } ;

/* Variables and functions */
 int AS3722_RTC_START_YEAR ; 
 int bcd2bin (int) ; 

__attribute__((used)) static void as3722_reg_to_time(u8 *rbuff, struct rtc_time *tm)
{
	tm->tm_sec = bcd2bin(rbuff[0] & 0x7F);
	tm->tm_min = bcd2bin(rbuff[1] & 0x7F);
	tm->tm_hour = bcd2bin(rbuff[2] & 0x3F);
	tm->tm_mday = bcd2bin(rbuff[3] & 0x3F);
	tm->tm_mon = bcd2bin(rbuff[4] & 0x1F) - 1;
	tm->tm_year = (AS3722_RTC_START_YEAR - 1900) + bcd2bin(rbuff[5] & 0x7F);
	return;
}