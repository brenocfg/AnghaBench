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
struct ltr501_gain {int scale; int uscale; } ;

/* Variables and functions */

__attribute__((used)) static int ltr501_get_gain_index(struct ltr501_gain *gain, int size,
				 int val, int val2)
{
	int i;

	for (i = 0; i < size; i++)
		if (val == gain[i].scale && val2 == gain[i].uscale)
			return i;

	return -1;
}