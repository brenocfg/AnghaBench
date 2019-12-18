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
typedef  int u64 ;
typedef  int u32 ;
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;

/* Variables and functions */
 scalar_t__ bin2bcd (int) ; 

__attribute__((used)) static void tm_to_opal(struct rtc_time *tm, u32 *y_m_d, u64 *h_m_s_ms)
{
	*y_m_d |= ((u32)bin2bcd((tm->tm_year + 1900) / 100)) << 24;
	*y_m_d |= ((u32)bin2bcd((tm->tm_year + 1900) % 100)) << 16;
	*y_m_d |= ((u32)bin2bcd((tm->tm_mon + 1))) << 8;
	*y_m_d |= ((u32)bin2bcd(tm->tm_mday));

	*h_m_s_ms |= ((u64)bin2bcd(tm->tm_hour)) << 56;
	*h_m_s_ms |= ((u64)bin2bcd(tm->tm_min)) << 48;
	*h_m_s_ms |= ((u64)bin2bcd(tm->tm_sec)) << 40;
}