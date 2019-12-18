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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ps3_os_area_set_rtc_diff (scalar_t__) ; 
 scalar_t__ read_rtc () ; 
 scalar_t__ rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static int ps3_set_time(struct device *dev, struct rtc_time *tm)
{
	ps3_os_area_set_rtc_diff(rtc_tm_to_time64(tm) - read_rtc());
	return 0;
}