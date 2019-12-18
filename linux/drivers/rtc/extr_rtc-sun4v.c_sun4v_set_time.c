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
 int hypervisor_set_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static int sun4v_set_time(struct device *dev, struct rtc_time *tm)
{
	return hypervisor_set_time(rtc_tm_to_time64(tm));
}