#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache {int /*<<< orphan*/  policy; TYPE_1__* ti; int /*<<< orphan*/  nr_dirty; int /*<<< orphan*/  dirty_bitset; } ;
typedef  int /*<<< orphan*/  dm_cblock_t ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_table_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_clear_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void force_clear_dirty(struct cache *cache, dm_cblock_t cblock)
{
	if (test_and_clear_bit(from_cblock(cblock), cache->dirty_bitset)) {
		if (atomic_dec_return(&cache->nr_dirty) == 0)
			dm_table_event(cache->ti->table);
	}

	policy_clear_dirty(cache->policy, cblock);
}