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
struct dm_disk_bitset {int /*<<< orphan*/  array_info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int dm_array_del (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dm_bitset_del(struct dm_disk_bitset *info, dm_block_t root)
{
	return dm_array_del(&info->array_info, root);
}