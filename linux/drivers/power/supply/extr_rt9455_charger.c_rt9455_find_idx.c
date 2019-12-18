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

__attribute__((used)) static unsigned int rt9455_find_idx(const int tbl[], int tbl_size, int v)
{
	int i;

	/*
	 * No need to iterate until the last index in the table because
	 * if no element greater than v is found in the table,
	 * or if only the last element is greater than v,
	 * function returns the index of the last element.
	 */
	for (i = 0; i < tbl_size - 1; i++)
		if (v <= tbl[i])
			return i;

	return (tbl_size - 1);
}