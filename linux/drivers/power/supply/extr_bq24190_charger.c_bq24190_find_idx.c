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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static u8 bq24190_find_idx(const int tbl[], int tbl_size, int v)
{
	int i;

	for (i = 1; i < tbl_size; i++)
		if (v < tbl[i])
			break;

	return i - 1;
}