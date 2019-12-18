#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int btemp_low_limit; int btemp_high_limit; int btemp_med_limit; } ;
struct TYPE_3__ {scalar_t__ btemp_medhigh; scalar_t__ btemp_lowmed; scalar_t__ btemp_high; scalar_t__ btemp_low; } ;
struct ab8500_btemp {int bat_temp; TYPE_2__ btemp_ranges; TYPE_1__ events; int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 scalar_t__ is_ab8500_3p3_or_earlier (int /*<<< orphan*/ ) ; 

int ab8500_btemp_get_temp(struct ab8500_btemp *di)
{
	int temp = 0;

	/*
	 * The BTEMP events are not reliabe on AB8500 cut3.3
	 * and prior versions
	 */
	if (is_ab8500_3p3_or_earlier(di->parent)) {
		temp = di->bat_temp * 10;
	} else {
		if (di->events.btemp_low) {
			if (temp > di->btemp_ranges.btemp_low_limit)
				temp = di->btemp_ranges.btemp_low_limit * 10;
			else
				temp = di->bat_temp * 10;
		} else if (di->events.btemp_high) {
			if (temp < di->btemp_ranges.btemp_high_limit)
				temp = di->btemp_ranges.btemp_high_limit * 10;
			else
				temp = di->bat_temp * 10;
		} else if (di->events.btemp_lowmed) {
			if (temp > di->btemp_ranges.btemp_med_limit)
				temp = di->btemp_ranges.btemp_med_limit * 10;
			else
				temp = di->bat_temp * 10;
		} else if (di->events.btemp_medhigh) {
			if (temp < di->btemp_ranges.btemp_med_limit)
				temp = di->btemp_ranges.btemp_med_limit * 10;
			else
				temp = di->bat_temp * 10;
		} else
			temp = di->bat_temp * 10;
	}
	return temp;
}