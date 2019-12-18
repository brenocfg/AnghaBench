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
typedef  int /*<<< orphan*/  u32 ;
struct rtc_time {void* tm_hour; void* tm_min; void* tm_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS_RTC_TIME_HR ; 
 int /*<<< orphan*/  CDNS_RTC_TIME_M ; 
 int /*<<< orphan*/  CDNS_RTC_TIME_S ; 
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* bcd2bin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cdns_rtc_reg2time(u32 reg, struct rtc_time *tm)
{
	tm->tm_sec  = bcd2bin(FIELD_GET(CDNS_RTC_TIME_S, reg));
	tm->tm_min  = bcd2bin(FIELD_GET(CDNS_RTC_TIME_M, reg));
	tm->tm_hour = bcd2bin(FIELD_GET(CDNS_RTC_TIME_HR, reg));
}