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
struct rtc_time {int dummy; } ;
struct cpcap_time {unsigned long day; unsigned long tod2; unsigned long tod1; } ;

/* Variables and functions */
 unsigned long SECS_PER_DAY ; 
 unsigned long TOD1_MASK ; 
 unsigned long TOD2_MASK ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 

__attribute__((used)) static void rtc2cpcap_time(struct cpcap_time *cpcap, struct rtc_time *rtc)
{
	unsigned long time;

	rtc_tm_to_time(rtc, &time);

	cpcap->day = time / SECS_PER_DAY;
	time %= SECS_PER_DAY;
	cpcap->tod2 = (time >> 8) & TOD2_MASK;
	cpcap->tod1 = time & TOD1_MASK;
}