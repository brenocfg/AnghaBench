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
struct dm_target {int dummy; } ;
struct dm_table {unsigned int depth; struct dm_target* targets; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 unsigned int KEYS_PER_NODE ; 
 scalar_t__ dm_table_get_size (struct dm_table*) ; 
 unsigned int get_child (unsigned int,unsigned int) ; 
 scalar_t__* get_node (struct dm_table*,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

struct dm_target *dm_table_find_target(struct dm_table *t, sector_t sector)
{
	unsigned int l, n = 0, k = 0;
	sector_t *node;

	if (unlikely(sector >= dm_table_get_size(t)))
		return NULL;

	for (l = 0; l < t->depth; l++) {
		n = get_child(n, k);
		node = get_node(t, l, n);

		for (k = 0; k < KEYS_PER_NODE; k++)
			if (node[k] >= sector)
				break;
	}

	return &t->targets[(KEYS_PER_NODE * n) + k];
}