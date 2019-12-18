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
struct journal_node {int /*<<< orphan*/  node; } ;
struct dm_integrity_c {int /*<<< orphan*/  journal_tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_journal_node (struct journal_node*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_journal_node(struct dm_integrity_c *ic, struct journal_node *node)
{
	BUG_ON(RB_EMPTY_NODE(&node->node));
	rb_erase(&node->node, &ic->journal_tree_root);
	init_journal_node(node);
}