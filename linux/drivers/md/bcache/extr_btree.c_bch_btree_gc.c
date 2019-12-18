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
struct gc_stat {int key_bytes; int data; } ;
struct closure {int dummy; } ;
struct cache_set {int /*<<< orphan*/  gc_stats; int /*<<< orphan*/  btree_gc_time; int /*<<< orphan*/  flags; } ;
struct btree_op {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_SET_IO_DISABLE ; 
 int EAGAIN ; 
 int /*<<< orphan*/  GC_SLEEP_MS ; 
 int /*<<< orphan*/  SHRT_MAX ; 
 int /*<<< orphan*/  bch_btree_gc_finish (struct cache_set*) ; 
 int /*<<< orphan*/  bch_btree_op_init (struct btree_op*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_moving_gc (struct cache_set*) ; 
 int /*<<< orphan*/  bch_time_stats_update (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_update_bucket_in_use (struct cache_set*,struct gc_stat*) ; 
 int /*<<< orphan*/  btree_gc_start (struct cache_set*) ; 
 int btree_root (int /*<<< orphan*/ ,struct cache_set*,struct btree_op*,struct closure*,struct gc_stat*) ; 
 int /*<<< orphan*/  closure_init_stack (struct closure*) ; 
 int /*<<< orphan*/  closure_sync (struct closure*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  gc_root ; 
 int /*<<< orphan*/  local_clock () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct gc_stat*,int) ; 
 int /*<<< orphan*/  memset (struct gc_stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_bcache_gc_end (struct cache_set*) ; 
 int /*<<< orphan*/  trace_bcache_gc_start (struct cache_set*) ; 
 int /*<<< orphan*/  wake_up_allocators (struct cache_set*) ; 

__attribute__((used)) static void bch_btree_gc(struct cache_set *c)
{
	int ret;
	struct gc_stat stats;
	struct closure writes;
	struct btree_op op;
	uint64_t start_time = local_clock();

	trace_bcache_gc_start(c);

	memset(&stats, 0, sizeof(struct gc_stat));
	closure_init_stack(&writes);
	bch_btree_op_init(&op, SHRT_MAX);

	btree_gc_start(c);

	/* if CACHE_SET_IO_DISABLE set, gc thread should stop too */
	do {
		ret = btree_root(gc_root, c, &op, &writes, &stats);
		closure_sync(&writes);
		cond_resched();

		if (ret == -EAGAIN)
			schedule_timeout_interruptible(msecs_to_jiffies
						       (GC_SLEEP_MS));
		else if (ret)
			pr_warn("gc failed!");
	} while (ret && !test_bit(CACHE_SET_IO_DISABLE, &c->flags));

	bch_btree_gc_finish(c);
	wake_up_allocators(c);

	bch_time_stats_update(&c->btree_gc_time, start_time);

	stats.key_bytes *= sizeof(uint64_t);
	stats.data	<<= 9;
	bch_update_bucket_in_use(c, &stats);
	memcpy(&c->gc_stats, &stats, sizeof(struct gc_stat));

	trace_bcache_gc_end(c);

	bch_moving_gc(c);
}