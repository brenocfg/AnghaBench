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
struct twl4030_madc_bat_calibration {int voltage; } ;

/* Variables and functions */

__attribute__((used)) static int twl4030_cmp(const void *a, const void *b)
{
	return ((struct twl4030_madc_bat_calibration *)b)->voltage -
		((struct twl4030_madc_bat_calibration *)a)->voltage;
}