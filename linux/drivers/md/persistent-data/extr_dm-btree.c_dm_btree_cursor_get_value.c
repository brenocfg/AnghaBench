#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct dm_btree_cursor {int depth; TYPE_3__* info; struct cursor_node* nodes; } ;
struct cursor_node {int /*<<< orphan*/  index; int /*<<< orphan*/  b; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct btree_node {TYPE_1__ header; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct TYPE_6__ {TYPE_2__ value_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODATA ; 
 int INTERNAL_NODE ; 
 struct btree_node* dm_block_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * key_ptr (struct btree_node*,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_ptr (struct btree_node*,int /*<<< orphan*/ ) ; 

int dm_btree_cursor_get_value(struct dm_btree_cursor *c, uint64_t *key, void *value_le)
{
	if (c->depth) {
		struct cursor_node *n = c->nodes + c->depth - 1;
		struct btree_node *bn = dm_block_data(n->b);

		if (le32_to_cpu(bn->header.flags) & INTERNAL_NODE)
			return -EINVAL;

		*key = le64_to_cpu(*key_ptr(bn, n->index));
		memcpy(value_le, value_ptr(bn, n->index), c->info->value_type.size);
		return 0;

	} else
		return -ENODATA;
}