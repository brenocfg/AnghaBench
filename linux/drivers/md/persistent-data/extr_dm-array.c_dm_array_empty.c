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
struct dm_array_info {int /*<<< orphan*/  btree_info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int dm_btree_empty (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int dm_array_empty(struct dm_array_info *info, dm_block_t *root)
{
	return dm_btree_empty(&info->btree_info, root);
}