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
typedef  unsigned int uint32_t ;
struct dm_btree_info {int dummy; } ;
struct child {struct btree_node* n; } ;
struct TYPE_2__ {scalar_t__ max_entries; int /*<<< orphan*/  nr_entries; } ;
struct btree_node {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  delete_center_node (struct dm_btree_info*,struct btree_node*,struct child*,struct child*,struct child*,struct btree_node*,struct btree_node*,struct btree_node*,unsigned int,unsigned int,unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int merge_threshold (struct btree_node*) ; 
 int /*<<< orphan*/  redistribute3 (struct dm_btree_info*,struct btree_node*,struct child*,struct child*,struct child*,struct btree_node*,struct btree_node*,struct btree_node*,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static void __rebalance3(struct dm_btree_info *info, struct btree_node *parent,
			 struct child *l, struct child *c, struct child *r)
{
	struct btree_node *left = l->n;
	struct btree_node *center = c->n;
	struct btree_node *right = r->n;

	uint32_t nr_left = le32_to_cpu(left->header.nr_entries);
	uint32_t nr_center = le32_to_cpu(center->header.nr_entries);
	uint32_t nr_right = le32_to_cpu(right->header.nr_entries);

	unsigned threshold = merge_threshold(left) * 4 + 1;

	BUG_ON(left->header.max_entries != center->header.max_entries);
	BUG_ON(center->header.max_entries != right->header.max_entries);

	if ((nr_left + nr_center + nr_right) < threshold)
		delete_center_node(info, parent, l, c, r, left, center, right,
				   nr_left, nr_center, nr_right);
	else
		redistribute3(info, parent, l, c, r, left, center, right,
			      nr_left, nr_center, nr_right);
}