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
typedef  int /*<<< orphan*/  uint64_t ;
struct dm_btree_info {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int dm_btree_find_key (struct dm_btree_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int dm_btree_find_lowest_key(struct dm_btree_info *info, dm_block_t root,
			     uint64_t *result_keys)
{
	return dm_btree_find_key(info, root, false, result_keys);
}