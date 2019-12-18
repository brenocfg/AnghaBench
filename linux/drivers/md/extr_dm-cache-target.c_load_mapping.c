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
typedef  int /*<<< orphan*/  uint32_t ;
struct cache {int /*<<< orphan*/  policy; int /*<<< orphan*/  dirty_bitset; int /*<<< orphan*/  nr_dirty; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 int policy_load_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int load_mapping(void *context, dm_oblock_t oblock, dm_cblock_t cblock,
			bool dirty, uint32_t hint, bool hint_valid)
{
	int r;
	struct cache *cache = context;

	if (dirty) {
		set_bit(from_cblock(cblock), cache->dirty_bitset);
		atomic_inc(&cache->nr_dirty);
	} else
		clear_bit(from_cblock(cblock), cache->dirty_bitset);

	r = policy_load_mapping(cache->policy, oblock, cblock, dirty, hint, hint_valid);
	if (r)
		return r;

	return 0;
}