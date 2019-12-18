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
struct dm_table {int depth; unsigned int* counts; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 scalar_t__ CHILDREN_PER_NODE ; 
 int KEYS_PER_NODE ; 
 unsigned int get_child (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/ * get_node (struct dm_table*,unsigned int,unsigned int) ; 

__attribute__((used)) static sector_t high(struct dm_table *t, unsigned int l, unsigned int n)
{
	for (; l < t->depth - 1; l++)
		n = get_child(n, CHILDREN_PER_NODE - 1);

	if (n >= t->counts[l])
		return (sector_t) - 1;

	return get_node(t, l, n)[KEYS_PER_NODE - 1];
}