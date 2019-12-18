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
 int EINVAL ; 
 int NUM_TRANGE_VALUES ; 
 int* trange_values ; 

__attribute__((used)) static int find_trange_value(int trange)
{
	int i;

	for (i = 0; i < NUM_TRANGE_VALUES; i++)
		if (trange_values[i] == trange)
			return i;

	return -EINVAL;
}