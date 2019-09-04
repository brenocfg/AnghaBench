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
struct child {unsigned int index; int /*<<< orphan*/  block; int /*<<< orphan*/  n; } ;
struct btree_node {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  btree_node_validator ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_location (int /*<<< orphan*/ ) ; 
 int dm_tm_shadow_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  inc_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_btree_value_type*) ; 
 int /*<<< orphan*/  value64 (struct btree_node*,unsigned int) ; 
 scalar_t__ value_ptr (struct btree_node*,unsigned int) ; 

__attribute__((used)) static int init_child(struct dm_btree_info *info, struct dm_btree_value_type *vt,
		      struct btree_node *parent,
		      unsigned index, struct child *result)
{
	int r, inc;
	dm_block_t root;

	result->index = index;
	root = value64(parent, index);

	r = dm_tm_shadow_block(info->tm, root, &btree_node_validator,
			       &result->block, &inc);
	if (r)
		return r;

	result->n = dm_block_data(result->block);

	if (inc)
		inc_children(info->tm, result->n, vt);

	*((__le64 *) value_ptr(parent, index)) =
		cpu_to_le64(dm_block_location(result->block));

	return 0;
}