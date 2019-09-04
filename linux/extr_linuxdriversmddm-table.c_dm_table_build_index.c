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
struct dm_table {int depth; unsigned int* counts; int /*<<< orphan*/  highs; int /*<<< orphan*/ * index; int /*<<< orphan*/  num_targets; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHILDREN_PER_NODE ; 
 int /*<<< orphan*/  KEYS_PER_NODE ; 
 unsigned int dm_div_up (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int int_log (unsigned int,int /*<<< orphan*/ ) ; 
 int setup_indexes (struct dm_table*) ; 

__attribute__((used)) static int dm_table_build_index(struct dm_table *t)
{
	int r = 0;
	unsigned int leaf_nodes;

	/* how many indexes will the btree have ? */
	leaf_nodes = dm_div_up(t->num_targets, KEYS_PER_NODE);
	t->depth = 1 + int_log(leaf_nodes, CHILDREN_PER_NODE);

	/* leaf layer has already been set up */
	t->counts[t->depth - 1] = leaf_nodes;
	t->index[t->depth - 1] = t->highs;

	if (t->depth >= 2)
		r = setup_indexes(t);

	return r;
}