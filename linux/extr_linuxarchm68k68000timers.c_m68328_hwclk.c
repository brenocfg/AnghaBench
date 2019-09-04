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
struct rtc_time {int tm_year; int tm_mday; long tm_hour; long tm_min; long tm_sec; scalar_t__ tm_mon; } ;

/* Variables and functions */
 long RTCTIME ; 

int m68328_hwclk(int set, struct rtc_time *t)
{
	if (!set) {
		long now = RTCTIME;
		t->tm_year = 1;
		t->tm_mon = 0;
		t->tm_mday = 1;
		t->tm_hour = (now >> 24) % 24;
		t->tm_min = (now >> 16) % 60;
		t->tm_sec = now % 60;
	}

	return 0;
}