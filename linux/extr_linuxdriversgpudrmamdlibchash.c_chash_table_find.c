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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct chash_iter {int slot; int /*<<< orphan*/  mask; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHASH_IN_RANGE (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  CHASH_ITER_INC (struct chash_iter) ; 
 struct chash_iter CHASH_ITER_INIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CHASH_ITER_SET (struct chash_iter,int) ; 
 int EINVAL ; 
 int chash_iter_hash (struct chash_iter) ; 
 scalar_t__ chash_iter_is_empty (struct chash_iter) ; 
 scalar_t__ chash_iter_is_valid (struct chash_iter) ; 
 scalar_t__ chash_iter_key (struct chash_iter) ; 
 int /*<<< orphan*/  chash_iter_relocate (struct chash_iter,struct chash_iter) ; 
 int /*<<< orphan*/  chash_iter_set_empty (struct chash_iter) ; 

__attribute__((used)) static int chash_table_find(struct chash_iter *iter, u64 key,
			    bool for_removal)
{
#ifdef CONFIG_CHASH_STATS
	u64 ts1 = local_clock();
#endif
	u32 hash = iter->slot;
	struct chash_iter first_redundant = CHASH_ITER_INIT(iter->table, -1);
	int first_avail = (for_removal ? -2 : -1);

	while (!chash_iter_is_valid(*iter) || chash_iter_key(*iter) != key) {
		if (chash_iter_is_empty(*iter)) {
			/* Found an empty slot, which ends the
			 * search. Clean up any preceding tombstones
			 * that are no longer needed because they lead
			 * to no-where
			 */
			if ((int)first_redundant.slot < 0)
				goto not_found;
			while (first_redundant.slot != iter->slot) {
				if (!chash_iter_is_valid(first_redundant))
					chash_iter_set_empty(first_redundant);
				CHASH_ITER_INC(first_redundant);
			}
#ifdef CHASH_DEBUG
			chash_table_check(iter->table);
#endif
			goto not_found;
		} else if (!chash_iter_is_valid(*iter)) {
			/* Found a tombstone. Remember it as candidate
			 * for relocating the entry we're looking for
			 * or for adding a new entry with the given key
			 */
			if (first_avail == -1)
				first_avail = iter->slot;
			/* Or mark it as the start of a series of
			 * potentially redundant tombstones
			 */
			else if (first_redundant.slot == -1)
				CHASH_ITER_SET(first_redundant, iter->slot);
		} else if (first_redundant.slot >= 0) {
			/* Found a valid, occupied slot with a
			 * preceding series of tombstones. Relocate it
			 * to a better position that no longer depends
			 * on those tombstones
			 */
			u32 cur_hash = chash_iter_hash(*iter);

			if (!CHASH_IN_RANGE(iter->table, cur_hash,
					    first_redundant.slot + 1,
					    iter->slot)) {
				/* This entry has a hash at or before
				 * the first tombstone we found. We
				 * can relocate it to that tombstone
				 * and advance to the next tombstone
				 */
				chash_iter_relocate(first_redundant, *iter);
				do {
					CHASH_ITER_INC(first_redundant);
				} while (chash_iter_is_valid(first_redundant));
			} else if (cur_hash != iter->slot) {
				/* Relocate entry to its home position
				 * or as close as possible so it no
				 * longer depends on any preceding
				 * tombstones
				 */
				struct chash_iter new_iter =
					CHASH_ITER_INIT(iter->table, cur_hash);

				while (new_iter.slot != iter->slot &&
				       chash_iter_is_valid(new_iter))
					CHASH_ITER_INC(new_iter);

				if (new_iter.slot != iter->slot)
					chash_iter_relocate(new_iter, *iter);
			}
		}

		CHASH_ITER_INC(*iter);
		if (iter->slot == hash) {
			iter->slot = -1;
			goto not_found;
		}
	}

#ifdef CONFIG_CHASH_STATS
	iter->table->hits++;
	iter->table->hits_steps += CHASH_SUB(iter->table, iter->slot, hash) + 1;
#endif

	if (first_avail >= 0) {
		CHASH_ITER_SET(first_redundant, first_avail);
		chash_iter_relocate(first_redundant, *iter);
		iter->slot = first_redundant.slot;
		iter->mask = first_redundant.mask;
	}

#ifdef CONFIG_CHASH_STATS
	iter->table->hits_time_ns += local_clock() - ts1;
#endif

	return 0;

not_found:
#ifdef CONFIG_CHASH_STATS
	iter->table->miss++;
	iter->table->miss_steps += (iter->slot < 0) ?
		(1 << iter->table->bits) :
		CHASH_SUB(iter->table, iter->slot, hash) + 1;
#endif

	if (first_avail >= 0)
		CHASH_ITER_SET(*iter, first_avail);

#ifdef CONFIG_CHASH_STATS
	iter->table->miss_time_ns += local_clock() - ts1;
#endif

	return -EINVAL;
}