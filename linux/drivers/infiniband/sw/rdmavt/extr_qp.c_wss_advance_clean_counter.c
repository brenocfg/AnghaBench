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
typedef  int /*<<< orphan*/  u64 ;
struct rvt_wss {int num_entries; int /*<<< orphan*/  total_count; int /*<<< orphan*/ * entries; int /*<<< orphan*/  clean_entry; int /*<<< orphan*/  clean_period; int /*<<< orphan*/  clean_counter; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int hweight64 (int /*<<< orphan*/ ) ; 
 unsigned long xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wss_advance_clean_counter(struct rvt_wss *wss)
{
	int entry;
	int weight;
	unsigned long bits;

	/* become the cleaner if we decrement the counter to zero */
	if (atomic_dec_and_test(&wss->clean_counter)) {
		/*
		 * Set, not add, the clean period.  This avoids an issue
		 * where the counter could decrement below the clean period.
		 * Doing a set can result in lost decrements, slowing the
		 * clean advance.  Since this a heuristic, this possible
		 * slowdown is OK.
		 *
		 * An alternative is to loop, advancing the counter by a
		 * clean period until the result is > 0. However, this could
		 * lead to several threads keeping another in the clean loop.
		 * This could be mitigated by limiting the number of times
		 * we stay in the loop.
		 */
		atomic_set(&wss->clean_counter, wss->clean_period);

		/*
		 * Uniquely grab the entry to clean and move to next.
		 * The current entry is always the lower bits of
		 * wss.clean_entry.  The table size, wss.num_entries,
		 * is always a power-of-2.
		 */
		entry = (atomic_inc_return(&wss->clean_entry) - 1)
			& (wss->num_entries - 1);

		/* clear the entry and count the bits */
		bits = xchg(&wss->entries[entry], 0);
		weight = hweight64((u64)bits);
		/* only adjust the contended total count if needed */
		if (weight)
			atomic_sub(weight, &wss->total_count);
	}
}