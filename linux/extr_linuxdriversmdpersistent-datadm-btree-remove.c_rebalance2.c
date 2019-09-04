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
struct shadow_spine {int dummy; } ;
struct dm_btree_value_type {int dummy; } ;
struct dm_btree_info {int dummy; } ;
struct child {int dummy; } ;
struct btree_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rebalance2 (struct dm_btree_info*,struct btree_node*,struct child*,struct child*) ; 
 struct btree_node* dm_block_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_child (struct dm_btree_info*,struct child*) ; 
 int init_child (struct dm_btree_info*,struct dm_btree_value_type*,struct btree_node*,unsigned int,struct child*) ; 
 int /*<<< orphan*/  shadow_current (struct shadow_spine*) ; 

__attribute__((used)) static int rebalance2(struct shadow_spine *s, struct dm_btree_info *info,
		      struct dm_btree_value_type *vt, unsigned left_index)
{
	int r;
	struct btree_node *parent;
	struct child left, right;

	parent = dm_block_data(shadow_current(s));

	r = init_child(info, vt, parent, left_index, &left);
	if (r)
		return r;

	r = init_child(info, vt, parent, left_index + 1, &right);
	if (r) {
		exit_child(info, &left);
		return r;
	}

	__rebalance2(info, parent, &left, &right);

	exit_child(info, &left);
	exit_child(info, &right);

	return 0;
}