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
 scalar_t__ ps3_os_area_get_rtc_diff () ; 
 scalar_t__ read_rtc () ; 
 int /*<<< orphan*/  rtc_time64_to_tm (scalar_t__,struct rtc_time*) ; 

__attribute__((used)) static int ps3_get_time(struct device *dev, struct rtc_time *tm)
{
	rtc_time64_to_tm(read_rtc() + ps3_os_area_get_rtc_diff(), tm);
	return 0;
}