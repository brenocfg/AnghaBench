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
typedef  int uint64_t ;
struct dm_cache_policy {int dummy; } ;
struct dm_cache_metadata {int /*<<< orphan*/  dirty_cursor; int /*<<< orphan*/  hint_cursor; int /*<<< orphan*/  mapping_cursor; int /*<<< orphan*/  cache_blocks; int /*<<< orphan*/  dirty_root; int /*<<< orphan*/  dirty_info; int /*<<< orphan*/  hint_root; int /*<<< orphan*/  hint_info; int /*<<< orphan*/  root; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  load_mapping_fn ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int __load_mapping_v1 (struct dm_cache_metadata*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int __load_mapping_v2 (struct dm_cache_metadata*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int dm_array_cursor_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_array_cursor_end (int /*<<< orphan*/ *) ; 
 int dm_array_cursor_next (int /*<<< orphan*/ *) ; 
 int dm_bitset_cursor_begin (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_bitset_cursor_end (int /*<<< orphan*/ *) ; 
 int dm_bitset_cursor_next (int /*<<< orphan*/ *) ; 
 int from_cblock (int /*<<< orphan*/ ) ; 
 int hints_array_available (struct dm_cache_metadata*,struct dm_cache_policy*) ; 
 scalar_t__ separate_dirty_bits (struct dm_cache_metadata*) ; 

__attribute__((used)) static int __load_mappings(struct dm_cache_metadata *cmd,
			   struct dm_cache_policy *policy,
			   load_mapping_fn fn, void *context)
{
	int r;
	uint64_t cb;

	bool hints_valid = hints_array_available(cmd, policy);

	if (from_cblock(cmd->cache_blocks) == 0)
		/* Nothing to do */
		return 0;

	r = dm_array_cursor_begin(&cmd->info, cmd->root, &cmd->mapping_cursor);
	if (r)
		return r;

	if (hints_valid) {
		r = dm_array_cursor_begin(&cmd->hint_info, cmd->hint_root, &cmd->hint_cursor);
		if (r) {
			dm_array_cursor_end(&cmd->mapping_cursor);
			return r;
		}
	}

	if (separate_dirty_bits(cmd)) {
		r = dm_bitset_cursor_begin(&cmd->dirty_info, cmd->dirty_root,
					   from_cblock(cmd->cache_blocks),
					   &cmd->dirty_cursor);
		if (r) {
			dm_array_cursor_end(&cmd->hint_cursor);
			dm_array_cursor_end(&cmd->mapping_cursor);
			return r;
		}
	}

	for (cb = 0; ; cb++) {
		if (separate_dirty_bits(cmd))
			r = __load_mapping_v2(cmd, cb, hints_valid,
					      &cmd->mapping_cursor,
					      &cmd->hint_cursor,
					      &cmd->dirty_cursor,
					      fn, context);
		else
			r = __load_mapping_v1(cmd, cb, hints_valid,
					      &cmd->mapping_cursor, &cmd->hint_cursor,
					      fn, context);
		if (r)
			goto out;

		/*
		 * We need to break out before we move the cursors.
		 */
		if (cb >= (from_cblock(cmd->cache_blocks) - 1))
			break;

		r = dm_array_cursor_next(&cmd->mapping_cursor);
		if (r) {
			DMERR("dm_array_cursor_next for mapping failed");
			goto out;
		}

		if (hints_valid) {
			r = dm_array_cursor_next(&cmd->hint_cursor);
			if (r) {
				dm_array_cursor_end(&cmd->hint_cursor);
				hints_valid = false;
			}
		}

		if (separate_dirty_bits(cmd)) {
			r = dm_bitset_cursor_next(&cmd->dirty_cursor);
			if (r) {
				DMERR("dm_bitset_cursor_next for dirty failed");
				goto out;
			}
		}
	}
out:
	dm_array_cursor_end(&cmd->mapping_cursor);
	if (hints_valid)
		dm_array_cursor_end(&cmd->hint_cursor);

	if (separate_dirty_bits(cmd))
		dm_bitset_cursor_end(&cmd->dirty_cursor);

	return r;
}