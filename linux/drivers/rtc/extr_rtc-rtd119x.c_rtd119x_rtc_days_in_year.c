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

/* Variables and functions */
 scalar_t__ is_leap_year (int) ; 

__attribute__((used)) static inline int rtd119x_rtc_days_in_year(int year)
{
	return 365 + (is_leap_year(year) ? 1 : 0);
}