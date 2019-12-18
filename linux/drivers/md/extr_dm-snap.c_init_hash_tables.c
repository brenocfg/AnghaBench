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
struct dm_snapshot {int /*<<< orphan*/  complete; int /*<<< orphan*/  pending; TYPE_1__* store; TYPE_2__* cow; } ;
typedef  int sector_t ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {int chunk_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CHUNK_CONSECUTIVE_BITS ; 
 int ENOMEM ; 
 int calc_max_buckets () ; 
 int /*<<< orphan*/  dm_exception_table_exit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dm_exception_table_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exception_cache ; 
 int get_dev_size (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int rounddown_pow_of_two (int) ; 

__attribute__((used)) static int init_hash_tables(struct dm_snapshot *s)
{
	sector_t hash_size, cow_dev_size, max_buckets;

	/*
	 * Calculate based on the size of the original volume or
	 * the COW volume...
	 */
	cow_dev_size = get_dev_size(s->cow->bdev);
	max_buckets = calc_max_buckets();

	hash_size = cow_dev_size >> s->store->chunk_shift;
	hash_size = min(hash_size, max_buckets);

	if (hash_size < 64)
		hash_size = 64;
	hash_size = rounddown_pow_of_two(hash_size);
	if (dm_exception_table_init(&s->complete, hash_size,
				    DM_CHUNK_CONSECUTIVE_BITS))
		return -ENOMEM;

	/*
	 * Allocate hash table for in-flight exceptions
	 * Make this smaller than the real hash table
	 */
	hash_size >>= 3;
	if (hash_size < 64)
		hash_size = 64;

	if (dm_exception_table_init(&s->pending, hash_size, 0)) {
		dm_exception_table_exit(&s->complete, exception_cache);
		return -ENOMEM;
	}

	return 0;
}