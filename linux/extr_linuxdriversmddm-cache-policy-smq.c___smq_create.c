#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_cache_policy {int dummy; } ;
struct TYPE_3__ {int nr_top_levels; int /*<<< orphan*/  nr_in_top_levels; } ;
struct smq_policy {unsigned int nr_hotspot_blocks; int cache_blocks_per_hotspot_block; unsigned int hotspot_level_jump; unsigned int write_promote_level; unsigned int read_promote_level; int migrations_allowed; int /*<<< orphan*/  es; int /*<<< orphan*/ * hotspot_hit_bits; int /*<<< orphan*/ * cache_hit_bits; int /*<<< orphan*/  table; int /*<<< orphan*/  hotspot_table; struct dm_cache_policy policy; int /*<<< orphan*/  bg_work; void* next_cache_period; void* next_hotspot_period; int /*<<< orphan*/  cache_stats; int /*<<< orphan*/  hotspot_stats; TYPE_1__ dirty; TYPE_1__ clean; int /*<<< orphan*/  cache_size; TYPE_1__ hotspot; int /*<<< orphan*/  lock; scalar_t__ tick; int /*<<< orphan*/  cache_alloc; int /*<<< orphan*/  hotspot_alloc; int /*<<< orphan*/  demote_sentinel_alloc; int /*<<< orphan*/  writeback_sentinel_alloc; int /*<<< orphan*/  cache_block_size; int /*<<< orphan*/  hotspot_block_size; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;
struct TYPE_4__ {int sentinel; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int NR_CACHE_LEVELS ; 
 unsigned int NR_HOTSPOT_LEVELS ; 
 void* alloc_bitset (int) ; 
 int /*<<< orphan*/  btracker_create (int) ; 
 int /*<<< orphan*/  calc_hotspot_params (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  clear_bitset (int /*<<< orphan*/ *,int) ; 
 int div64_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_bitset (int /*<<< orphan*/ *) ; 
 int from_cblock (int /*<<< orphan*/ ) ; 
 TYPE_2__* get_entry (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  h_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ h_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_allocator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  init_policy_functions (struct smq_policy*,int) ; 
 void* jiffies ; 
 int /*<<< orphan*/  kfree (struct smq_policy*) ; 
 struct smq_policy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (unsigned int,int) ; 
 int /*<<< orphan*/  q_init (TYPE_1__*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  sentinels_init (struct smq_policy*) ; 
 int /*<<< orphan*/  space_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ space_init (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_init (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static struct dm_cache_policy *__smq_create(dm_cblock_t cache_size,
					    sector_t origin_size,
					    sector_t cache_block_size,
					    bool mimic_mq,
					    bool migrations_allowed)
{
	unsigned i;
	unsigned nr_sentinels_per_queue = 2u * NR_CACHE_LEVELS;
	unsigned total_sentinels = 2u * nr_sentinels_per_queue;
	struct smq_policy *mq = kzalloc(sizeof(*mq), GFP_KERNEL);

	if (!mq)
		return NULL;

	init_policy_functions(mq, mimic_mq);
	mq->cache_size = cache_size;
	mq->cache_block_size = cache_block_size;

	calc_hotspot_params(origin_size, cache_block_size, from_cblock(cache_size),
			    &mq->hotspot_block_size, &mq->nr_hotspot_blocks);

	mq->cache_blocks_per_hotspot_block = div64_u64(mq->hotspot_block_size, mq->cache_block_size);
	mq->hotspot_level_jump = 1u;
	if (space_init(&mq->es, total_sentinels + mq->nr_hotspot_blocks + from_cblock(cache_size))) {
		DMERR("couldn't initialize entry space");
		goto bad_pool_init;
	}

	init_allocator(&mq->writeback_sentinel_alloc, &mq->es, 0, nr_sentinels_per_queue);
	for (i = 0; i < nr_sentinels_per_queue; i++)
		get_entry(&mq->writeback_sentinel_alloc, i)->sentinel = true;

	init_allocator(&mq->demote_sentinel_alloc, &mq->es, nr_sentinels_per_queue, total_sentinels);
	for (i = 0; i < nr_sentinels_per_queue; i++)
		get_entry(&mq->demote_sentinel_alloc, i)->sentinel = true;

	init_allocator(&mq->hotspot_alloc, &mq->es, total_sentinels,
		       total_sentinels + mq->nr_hotspot_blocks);

	init_allocator(&mq->cache_alloc, &mq->es,
		       total_sentinels + mq->nr_hotspot_blocks,
		       total_sentinels + mq->nr_hotspot_blocks + from_cblock(cache_size));

	mq->hotspot_hit_bits = alloc_bitset(mq->nr_hotspot_blocks);
	if (!mq->hotspot_hit_bits) {
		DMERR("couldn't allocate hotspot hit bitset");
		goto bad_hotspot_hit_bits;
	}
	clear_bitset(mq->hotspot_hit_bits, mq->nr_hotspot_blocks);

	if (from_cblock(cache_size)) {
		mq->cache_hit_bits = alloc_bitset(from_cblock(cache_size));
		if (!mq->cache_hit_bits) {
			DMERR("couldn't allocate cache hit bitset");
			goto bad_cache_hit_bits;
		}
		clear_bitset(mq->cache_hit_bits, from_cblock(mq->cache_size));
	} else
		mq->cache_hit_bits = NULL;

	mq->tick = 0;
	spin_lock_init(&mq->lock);

	q_init(&mq->hotspot, &mq->es, NR_HOTSPOT_LEVELS);
	mq->hotspot.nr_top_levels = 8;
	mq->hotspot.nr_in_top_levels = min(mq->nr_hotspot_blocks / NR_HOTSPOT_LEVELS,
					   from_cblock(mq->cache_size) / mq->cache_blocks_per_hotspot_block);

	q_init(&mq->clean, &mq->es, NR_CACHE_LEVELS);
	q_init(&mq->dirty, &mq->es, NR_CACHE_LEVELS);

	stats_init(&mq->hotspot_stats, NR_HOTSPOT_LEVELS);
	stats_init(&mq->cache_stats, NR_CACHE_LEVELS);

	if (h_init(&mq->table, &mq->es, from_cblock(cache_size)))
		goto bad_alloc_table;

	if (h_init(&mq->hotspot_table, &mq->es, mq->nr_hotspot_blocks))
		goto bad_alloc_hotspot_table;

	sentinels_init(mq);
	mq->write_promote_level = mq->read_promote_level = NR_HOTSPOT_LEVELS;

	mq->next_hotspot_period = jiffies;
	mq->next_cache_period = jiffies;

	mq->bg_work = btracker_create(4096); /* FIXME: hard coded value */
	if (!mq->bg_work)
		goto bad_btracker;

	mq->migrations_allowed = migrations_allowed;

	return &mq->policy;

bad_btracker:
	h_exit(&mq->hotspot_table);
bad_alloc_hotspot_table:
	h_exit(&mq->table);
bad_alloc_table:
	free_bitset(mq->cache_hit_bits);
bad_cache_hit_bits:
	free_bitset(mq->hotspot_hit_bits);
bad_hotspot_hit_bits:
	space_exit(&mq->es);
bad_pool_init:
	kfree(mq);

	return NULL;
}