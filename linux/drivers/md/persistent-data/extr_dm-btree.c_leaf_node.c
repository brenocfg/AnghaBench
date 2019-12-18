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
struct dm_btree_cursor {int depth; struct cursor_node* nodes; } ;
struct cursor_node {int /*<<< orphan*/  b; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct btree_node {TYPE_1__ header; } ;

/* Variables and functions */
 int LEAF_NODE ; 
 struct btree_node* dm_block_data (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool leaf_node(struct dm_btree_cursor *c)
{
	struct cursor_node *n = c->nodes + c->depth - 1;
	struct btree_node *bn = dm_block_data(n->b);

	return le32_to_cpu(bn->header.flags) & LEAF_NODE;
}