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
struct dm_transaction_manager {int /*<<< orphan*/  bm; int /*<<< orphan*/  sm; } ;
struct dm_block_validator {int dummy; } ;
struct dm_block {int dummy; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_block_size (int /*<<< orphan*/ ) ; 
 int dm_bm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_block_validator*,struct dm_block**) ; 
 int /*<<< orphan*/  dm_bm_unlock (struct dm_block*) ; 
 int dm_bm_write_lock_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_block_validator*,struct dm_block**) ; 
 int dm_sm_dec_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dm_sm_new_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __shadow_block(struct dm_transaction_manager *tm, dm_block_t orig,
			  struct dm_block_validator *v,
			  struct dm_block **result)
{
	int r;
	dm_block_t new;
	struct dm_block *orig_block;

	r = dm_sm_new_block(tm->sm, &new);
	if (r < 0)
		return r;

	r = dm_sm_dec_block(tm->sm, orig);
	if (r < 0)
		return r;

	r = dm_bm_read_lock(tm->bm, orig, v, &orig_block);
	if (r < 0)
		return r;

	/*
	 * It would be tempting to use dm_bm_unlock_move here, but some
	 * code, such as the space maps, keeps using the old data structures
	 * secure in the knowledge they won't be changed until the next
	 * transaction.  Using unlock_move would force a synchronous read
	 * since the old block would no longer be in the cache.
	 */
	r = dm_bm_write_lock_zero(tm->bm, new, v, result);
	if (r) {
		dm_bm_unlock(orig_block);
		return r;
	}

	memcpy(dm_block_data(*result), dm_block_data(orig_block),
	       dm_bm_block_size(tm->bm));

	dm_bm_unlock(orig_block);
	return r;
}