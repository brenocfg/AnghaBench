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
struct rtc_time {int tm_mday; int tm_wday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 int RDxR_DOW_MASK ; 
 int RDxR_DOW_S ; 
 int RDxR_HOUR_S ; 
 int RDxR_MIN_S ; 
 int RDxR_WOM_MASK ; 
 int RDxR_WOM_S ; 

__attribute__((used)) static u32 rdxr_calc(struct rtc_time *tm)
{
	return ((((tm->tm_mday + 6) / 7) << RDxR_WOM_S) & RDxR_WOM_MASK)
		| (((tm->tm_wday + 1) << RDxR_DOW_S) & RDxR_DOW_MASK)
		| (tm->tm_hour << RDxR_HOUR_S)
		| (tm->tm_min << RDxR_MIN_S)
		| tm->tm_sec;
}