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
typedef  int u32 ;
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_wday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int RDxR_DOW_MASK ; 
 int RDxR_DOW_S ; 
 int RDxR_HOUR_MASK ; 
 int RDxR_HOUR_S ; 
 int RDxR_MIN_MASK ; 
 int RDxR_MIN_S ; 
 int RDxR_SEC_MASK ; 
 int RYxR_DAY_MASK ; 
 int RYxR_MONTH_MASK ; 
 int RYxR_MONTH_S ; 
 int RYxR_YEAR_MASK ; 
 int RYxR_YEAR_S ; 

__attribute__((used)) static void tm_calc(u32 rycr, u32 rdcr, struct rtc_time *tm)
{
	tm->tm_year = ((rycr & RYxR_YEAR_MASK) >> RYxR_YEAR_S) - 1900;
	tm->tm_mon = (((rycr & RYxR_MONTH_MASK) >> RYxR_MONTH_S)) - 1;
	tm->tm_mday = (rycr & RYxR_DAY_MASK);
	tm->tm_wday = ((rycr & RDxR_DOW_MASK) >> RDxR_DOW_S) - 1;
	tm->tm_hour = (rdcr & RDxR_HOUR_MASK) >> RDxR_HOUR_S;
	tm->tm_min = (rdcr & RDxR_MIN_MASK) >> RDxR_MIN_S;
	tm->tm_sec = rdcr & RDxR_SEC_MASK;
}