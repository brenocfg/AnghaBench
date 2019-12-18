#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sampling_int; int sampling_fract; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* isl29028_prox_data ; 

__attribute__((used)) static int isl29028_find_prox_sleep_index(int sampling_int, int sampling_fract)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(isl29028_prox_data); ++i) {
		if (isl29028_prox_data[i].sampling_int == sampling_int &&
		    isl29028_prox_data[i].sampling_fract == sampling_fract)
			return i;
	}

	return -EINVAL;
}