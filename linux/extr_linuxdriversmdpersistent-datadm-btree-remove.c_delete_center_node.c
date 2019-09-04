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
typedef  scalar_t__ uint32_t ;
struct dm_btree_info {int /*<<< orphan*/  tm; } ;
struct child {int /*<<< orphan*/  block; int /*<<< orphan*/  index; } ;
struct TYPE_2__ {void* nr_entries; int /*<<< orphan*/  max_entries; } ;
struct btree_node {int /*<<< orphan*/ * keys; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __rebalance2 (struct dm_btree_info*,struct btree_node*,struct child*,struct child*) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  delete_at (struct btree_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_location (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * key_ptr (struct btree_node*,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned int min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  node_copy (struct btree_node*,struct btree_node*,unsigned int) ; 
 int /*<<< orphan*/  node_shift (struct btree_node*,unsigned int) ; 

__attribute__((used)) static void delete_center_node(struct dm_btree_info *info, struct btree_node *parent,
			       struct child *l, struct child *c, struct child *r,
			       struct btree_node *left, struct btree_node *center, struct btree_node *right,
			       uint32_t nr_left, uint32_t nr_center, uint32_t nr_right)
{
	uint32_t max_entries = le32_to_cpu(left->header.max_entries);
	unsigned shift = min(max_entries - nr_left, nr_center);

	BUG_ON(nr_left + shift > max_entries);
	node_copy(left, center, -shift);
	left->header.nr_entries = cpu_to_le32(nr_left + shift);

	if (shift != nr_center) {
		shift = nr_center - shift;
		BUG_ON((nr_right + shift) > max_entries);
		node_shift(right, shift);
		node_copy(center, right, shift);
		right->header.nr_entries = cpu_to_le32(nr_right + shift);
	}
	*key_ptr(parent, r->index) = right->keys[0];

	delete_at(parent, c->index);
	r->index--;

	dm_tm_dec(info->tm, dm_block_location(c->block));
	__rebalance2(info, parent, l, r);
}