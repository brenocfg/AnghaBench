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
struct rtc_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_rtc_hctosys (struct rtc_device*) ; 
 int /*<<< orphan*/  proc_create_single_data (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rtc_device*) ; 
 int /*<<< orphan*/  rtc_proc_show ; 

void rtc_proc_add_device(struct rtc_device *rtc)
{
	if (is_rtc_hctosys(rtc))
		proc_create_single_data("driver/rtc", 0, NULL, rtc_proc_show,
					rtc);
}