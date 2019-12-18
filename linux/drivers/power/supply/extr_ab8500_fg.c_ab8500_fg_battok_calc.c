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
struct ab8500_fg {int dummy; } ;

/* Variables and functions */
 int BATT_OK_INCREMENT ; 
 int BATT_OK_MAX_NR_INCREMENTS ; 
 int BATT_OK_MIN ; 

__attribute__((used)) static int ab8500_fg_battok_calc(struct ab8500_fg *di, int target)
{
	if (target > BATT_OK_MIN +
		(BATT_OK_INCREMENT * BATT_OK_MAX_NR_INCREMENTS))
		return BATT_OK_MAX_NR_INCREMENTS;
	if (target < BATT_OK_MIN)
		return 0;
	return (target - BATT_OK_MIN) / BATT_OK_INCREMENT;
}