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
struct dm_btree_cursor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int find_leaf (struct dm_btree_cursor*) ; 
 int inc_or_backtrack (struct dm_btree_cursor*) ; 

int dm_btree_cursor_next(struct dm_btree_cursor *c)
{
	int r = inc_or_backtrack(c);
	if (!r) {
		r = find_leaf(c);
		if (r)
			DMERR("find_leaf failed");
	}

	return r;
}