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
struct armada_thermal_data {int hyst_mask; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned int*) ; 
 unsigned int* hyst_levels_mc ; 

__attribute__((used)) static unsigned int armada_mc_to_reg_hyst(struct armada_thermal_data *data,
					  unsigned int hyst_mc)
{
	int i;

	/*
	 * We will always take the smallest possible hysteresis to avoid risking
	 * the hardware integrity by enlarging the threshold by +8°C in the
	 * worst case.
	 */
	for (i = ARRAY_SIZE(hyst_levels_mc) - 1; i > 0; i--)
		if (hyst_mc >= hyst_levels_mc[i])
			break;

	return i & data->hyst_mask;
}