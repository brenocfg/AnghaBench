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
typedef  int u32 ;

/* Variables and functions */
 int* cmd_table ; 

__attribute__((used)) static u32 *ps3av_search_cmd_table(u32 cid, u32 mask)
{
	u32 *table;
	int i;

	table = cmd_table;
	for (i = 0;; table++, i++) {
		if ((*table & mask) == (cid & mask))
			break;
		if (*table == 0)
			return NULL;
	}
	return table;
}