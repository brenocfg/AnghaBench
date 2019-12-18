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
struct ab8500_btemp {int bat_temp; } ;

/* Variables and functions */

int ab8500_btemp_get_batctrl_temp(struct ab8500_btemp *btemp)
{
	return btemp->bat_temp * 1000;
}