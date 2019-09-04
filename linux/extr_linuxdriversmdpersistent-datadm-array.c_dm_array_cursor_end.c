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
struct dm_array_cursor {int /*<<< orphan*/  cursor; scalar_t__ block; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_btree_cursor_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_ablock (int /*<<< orphan*/ ,scalar_t__) ; 

void dm_array_cursor_end(struct dm_array_cursor *c)
{
	if (c->block) {
		unlock_ablock(c->info, c->block);
		dm_btree_cursor_end(&c->cursor);
	}
}