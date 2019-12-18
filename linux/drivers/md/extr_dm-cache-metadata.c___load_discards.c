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
typedef  int uint32_t ;
struct dm_cache_metadata {int /*<<< orphan*/  discard_block_size; int /*<<< orphan*/  discard_nr_blocks; int /*<<< orphan*/  discard_root; int /*<<< orphan*/  discard_info; scalar_t__ clean_when_opened; } ;
struct dm_bitset_cursor {int dummy; } ;
typedef  int (* load_discard_fn ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;

/* Variables and functions */
 int dm_bitset_cursor_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct dm_bitset_cursor*) ; 
 int /*<<< orphan*/  dm_bitset_cursor_end (struct dm_bitset_cursor*) ; 
 int dm_bitset_cursor_get_value (struct dm_bitset_cursor*) ; 
 int dm_bitset_cursor_next (struct dm_bitset_cursor*) ; 
 int dm_bitset_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int from_dblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_dblock (int) ; 

__attribute__((used)) static int __load_discards(struct dm_cache_metadata *cmd,
			   load_discard_fn fn, void *context)
{
	int r = 0;
	uint32_t b;
	struct dm_bitset_cursor c;

	if (from_dblock(cmd->discard_nr_blocks) == 0)
		/* nothing to do */
		return 0;

	if (cmd->clean_when_opened) {
		r = dm_bitset_flush(&cmd->discard_info, cmd->discard_root, &cmd->discard_root);
		if (r)
			return r;

		r = dm_bitset_cursor_begin(&cmd->discard_info, cmd->discard_root,
					   from_dblock(cmd->discard_nr_blocks), &c);
		if (r)
			return r;

		for (b = 0; ; b++) {
			r = fn(context, cmd->discard_block_size, to_dblock(b),
			       dm_bitset_cursor_get_value(&c));
			if (r)
				break;

			if (b >= (from_dblock(cmd->discard_nr_blocks) - 1))
				break;

			r = dm_bitset_cursor_next(&c);
			if (r)
				break;
		}

		dm_bitset_cursor_end(&c);

	} else {
		for (b = 0; b < from_dblock(cmd->discard_nr_blocks); b++) {
			r = fn(context, cmd->discard_block_size, to_dblock(b), false);
			if (r)
				return r;
		}
	}

	return r;
}