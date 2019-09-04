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
 int get_temp_mc (void*,int) ; 
 int ntc_thermistor_get_ohm (void*) ; 

__attribute__((used)) static int ntc_read_temp(void *data, int *temp)
{
	int ohm;

	ohm = ntc_thermistor_get_ohm(data);
	if (ohm < 0)
		return ohm;

	*temp = get_temp_mc(data, ohm);

	return 0;
}