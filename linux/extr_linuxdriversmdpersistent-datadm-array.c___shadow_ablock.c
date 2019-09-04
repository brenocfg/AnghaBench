#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dm_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tm; } ;
struct dm_array_info {TYPE_1__ btree_info; } ;
struct array_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  array_validator ; 
 struct array_block* dm_block_data (struct dm_block*) ; 
 int dm_tm_shadow_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**,int*) ; 
 int /*<<< orphan*/  inc_ablock_entries (struct dm_array_info*,struct array_block*) ; 

__attribute__((used)) static int __shadow_ablock(struct dm_array_info *info, dm_block_t b,
			   struct dm_block **block, struct array_block **ab)
{
	int inc;
	int r = dm_tm_shadow_block(info->btree_info.tm, b,
				   &array_validator, block, &inc);
	if (r)
		return r;

	*ab = dm_block_data(*block);
	if (inc)
		inc_ablock_entries(info, *ab);

	return 0;
}