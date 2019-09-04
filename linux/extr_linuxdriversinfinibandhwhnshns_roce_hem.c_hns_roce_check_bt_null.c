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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static bool hns_roce_check_bt_null(u64 **bt, u64 start_idx, u32 bt_chunk_num)
{
	int i;

	for (i = 0; i < bt_chunk_num; i++)
		if (bt[start_idx + i])
			return false;

	return true;
}