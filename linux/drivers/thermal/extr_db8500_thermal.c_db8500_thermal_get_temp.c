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
struct db8500_thermal_zone {int interpolated_temp; } ;

/* Variables and functions */

__attribute__((used)) static int db8500_thermal_get_temp(void *data, int *temp)
{
	struct db8500_thermal_zone *th = data;

	/*
	 * TODO: There is no PRCMU interface to get temperature data currently,
	 * so a pseudo temperature is returned , it works for thermal framework
	 * and this will be fixed when the PRCMU interface is available.
	 */
	*temp = th->interpolated_temp;

	return 0;
}