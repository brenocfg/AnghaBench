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
struct timespec {int /*<<< orphan*/  tv_sec; } ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtc_sh_get_time (struct timespec*) ; 
 int /*<<< orphan*/  rtc_time_to_tm (int /*<<< orphan*/ ,struct rtc_time*) ; 

__attribute__((used)) static int rtc_generic_get_time(struct device *dev, struct rtc_time *tm)
{
	struct timespec tv;

	rtc_sh_get_time(&tv);
	rtc_time_to_tm(tv.tv_sec, tm);
	return 0;
}