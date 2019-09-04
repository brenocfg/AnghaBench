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
struct dm_block {int dummy; } ;
struct dm_array_info {int /*<<< orphan*/  btree_info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  __dm_bless_for_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_location (struct dm_block*) ; 
 int dm_btree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int insert_ablock(struct dm_array_info *info, uint64_t index,
			 struct dm_block *block, dm_block_t *root)
{
	__le64 block_le = cpu_to_le64(dm_block_location(block));

	__dm_bless_for_disk(block_le);
	return dm_btree_insert(&info->btree_info, *root, &index, &block_le, root);
}