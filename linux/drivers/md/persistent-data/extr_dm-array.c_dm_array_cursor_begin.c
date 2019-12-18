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
struct dm_array_info {int /*<<< orphan*/  btree_info; } ;
struct dm_array_cursor {int /*<<< orphan*/  cursor; struct dm_array_info* info; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int dm_btree_cursor_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int load_ablock (struct dm_array_cursor*) ; 
 int /*<<< orphan*/  memset (struct dm_array_cursor*,int /*<<< orphan*/ ,int) ; 

int dm_array_cursor_begin(struct dm_array_info *info, dm_block_t root,
			  struct dm_array_cursor *c)
{
	int r;

	memset(c, 0, sizeof(*c));
	c->info = info;
	r = dm_btree_cursor_begin(&info->btree_info, root, true, &c->cursor);
	if (r) {
		DMERR("couldn't create btree cursor");
		return r;
	}

	return load_ablock(c);
}