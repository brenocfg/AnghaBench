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
 size_t is_leap_year (unsigned int) ; 
 int** rtc_ydays ; 

int rtc_year_days(unsigned int day, unsigned int month, unsigned int year)
{
	return rtc_ydays[is_leap_year(year)][month] + day - 1;
}