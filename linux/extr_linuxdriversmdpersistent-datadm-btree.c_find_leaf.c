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
typedef  int /*<<< orphan*/  value_le ;
struct dm_btree_cursor {int depth; struct cursor_node* nodes; } ;
struct cursor_node {int /*<<< orphan*/  index; int /*<<< orphan*/  b; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  flags; } ;
struct btree_node {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int ENODATA ; 
 int LEAF_NODE ; 
 struct btree_node* dm_block_data (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int push_node (struct dm_btree_cursor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_ptr (struct btree_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_leaf(struct dm_btree_cursor *c)
{
	int r = 0;
	struct cursor_node *n;
	struct btree_node *bn;
	__le64 value_le;

	for (;;) {
		n = c->nodes + c->depth - 1;
		bn = dm_block_data(n->b);

		if (le32_to_cpu(bn->header.flags) & LEAF_NODE)
			break;

		memcpy(&value_le, value_ptr(bn, n->index), sizeof(value_le));
		r = push_node(c, le64_to_cpu(value_le));
		if (r) {
			DMERR("push_node failed");
			break;
		}
	}

	if (!r && (le32_to_cpu(bn->header.nr_entries) == 0))
		return -ENODATA;

	return r;
}