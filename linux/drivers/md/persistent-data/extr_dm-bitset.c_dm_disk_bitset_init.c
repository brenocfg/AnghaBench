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
struct dm_transaction_manager {int dummy; } ;
struct dm_disk_bitset {int current_index_set; int /*<<< orphan*/  array_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitset_bvt ; 
 int /*<<< orphan*/  dm_array_info_init (int /*<<< orphan*/ *,struct dm_transaction_manager*,int /*<<< orphan*/ *) ; 

void dm_disk_bitset_init(struct dm_transaction_manager *tm,
			 struct dm_disk_bitset *info)
{
	dm_array_info_init(&info->array_info, tm, &bitset_bvt);
	info->current_index_set = false;
}