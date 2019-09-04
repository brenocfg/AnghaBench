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
struct dm_btree_value_type {int dummy; } ;
struct dm_btree_info {int /*<<< orphan*/  tm; } ;
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  btree_node_validator ; 
 int /*<<< orphan*/  dm_block_data (struct dm_block*) ; 
 int dm_tm_shadow_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**,int*) ; 
 int /*<<< orphan*/  inc_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_btree_value_type*) ; 

__attribute__((used)) static int bn_shadow(struct dm_btree_info *info, dm_block_t orig,
	      struct dm_btree_value_type *vt,
	      struct dm_block **result)
{
	int r, inc;

	r = dm_tm_shadow_block(info->tm, orig, &btree_node_validator,
			       result, &inc);
	if (!r && inc)
		inc_children(info->tm, dm_block_data(*result), vt);

	return r;
}