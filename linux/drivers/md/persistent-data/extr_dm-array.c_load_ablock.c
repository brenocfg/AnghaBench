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
typedef  int /*<<< orphan*/  uint64_t ;
struct dm_array_cursor {int /*<<< orphan*/  cursor; int /*<<< orphan*/ * ab; int /*<<< orphan*/ * block; int /*<<< orphan*/  info; scalar_t__ index; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  dm_btree_cursor_end (int /*<<< orphan*/ *) ; 
 int dm_btree_cursor_get_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int get_ablock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_ablock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int load_ablock(struct dm_array_cursor *c)
{
	int r;
	__le64 value_le;
	uint64_t key;

	if (c->block)
		unlock_ablock(c->info, c->block);

	c->block = NULL;
	c->ab = NULL;
	c->index = 0;

	r = dm_btree_cursor_get_value(&c->cursor, &key, &value_le);
	if (r) {
		DMERR("dm_btree_cursor_get_value failed");
		dm_btree_cursor_end(&c->cursor);

	} else {
		r = get_ablock(c->info, le64_to_cpu(value_le), &c->block, &c->ab);
		if (r) {
			DMERR("get_ablock failed");
			dm_btree_cursor_end(&c->cursor);
		}
	}

	return r;
}