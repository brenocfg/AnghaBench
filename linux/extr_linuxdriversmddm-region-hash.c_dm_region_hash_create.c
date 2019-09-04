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
struct dm_region_hash {void (* dispatch_bios ) (void*,struct bio_list*) ;void (* wakeup_workers ) (void*) ;void (* wakeup_all_recovery_waiters ) (void*) ;unsigned int max_recovery; unsigned int mask; unsigned int nr_buckets; int /*<<< orphan*/ * buckets; int /*<<< orphan*/  region_pool; scalar_t__ flush_failure; int /*<<< orphan*/  failed_recovered_regions; int /*<<< orphan*/  recovered_regions; int /*<<< orphan*/  quiesced_regions; int /*<<< orphan*/  clean_regions; int /*<<< orphan*/  recovery_in_flight; int /*<<< orphan*/  recovery_count; int /*<<< orphan*/  region_lock; int /*<<< orphan*/  prime; int /*<<< orphan*/  shift; int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  region_shift; int /*<<< orphan*/  region_size; struct dm_dirty_log* log; int /*<<< orphan*/  target_begin; void* context; } ;
struct dm_region {int dummy; } ;
struct dm_dirty_log {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;
typedef  int region_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct dm_region_hash* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MIN_REGIONS ; 
 int /*<<< orphan*/  RH_HASH_MULT ; 
 int /*<<< orphan*/  RH_HASH_SHIFT ; 
 int /*<<< orphan*/  __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  array_size (unsigned int,int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct dm_region_hash*) ; 
 struct dm_region_hash* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mempool_init_kmalloc_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmalloc (int /*<<< orphan*/ ) ; 

struct dm_region_hash *dm_region_hash_create(
		void *context, void (*dispatch_bios)(void *context,
						     struct bio_list *bios),
		void (*wakeup_workers)(void *context),
		void (*wakeup_all_recovery_waiters)(void *context),
		sector_t target_begin, unsigned max_recovery,
		struct dm_dirty_log *log, uint32_t region_size,
		region_t nr_regions)
{
	struct dm_region_hash *rh;
	unsigned nr_buckets, max_buckets;
	size_t i;
	int ret;

	/*
	 * Calculate a suitable number of buckets for our hash
	 * table.
	 */
	max_buckets = nr_regions >> 6;
	for (nr_buckets = 128u; nr_buckets < max_buckets; nr_buckets <<= 1)
		;
	nr_buckets >>= 1;

	rh = kzalloc(sizeof(*rh), GFP_KERNEL);
	if (!rh) {
		DMERR("unable to allocate region hash memory");
		return ERR_PTR(-ENOMEM);
	}

	rh->context = context;
	rh->dispatch_bios = dispatch_bios;
	rh->wakeup_workers = wakeup_workers;
	rh->wakeup_all_recovery_waiters = wakeup_all_recovery_waiters;
	rh->target_begin = target_begin;
	rh->max_recovery = max_recovery;
	rh->log = log;
	rh->region_size = region_size;
	rh->region_shift = __ffs(region_size);
	rwlock_init(&rh->hash_lock);
	rh->mask = nr_buckets - 1;
	rh->nr_buckets = nr_buckets;

	rh->shift = RH_HASH_SHIFT;
	rh->prime = RH_HASH_MULT;

	rh->buckets = vmalloc(array_size(nr_buckets, sizeof(*rh->buckets)));
	if (!rh->buckets) {
		DMERR("unable to allocate region hash bucket memory");
		kfree(rh);
		return ERR_PTR(-ENOMEM);
	}

	for (i = 0; i < nr_buckets; i++)
		INIT_LIST_HEAD(rh->buckets + i);

	spin_lock_init(&rh->region_lock);
	sema_init(&rh->recovery_count, 0);
	atomic_set(&rh->recovery_in_flight, 0);
	INIT_LIST_HEAD(&rh->clean_regions);
	INIT_LIST_HEAD(&rh->quiesced_regions);
	INIT_LIST_HEAD(&rh->recovered_regions);
	INIT_LIST_HEAD(&rh->failed_recovered_regions);
	rh->flush_failure = 0;

	ret = mempool_init_kmalloc_pool(&rh->region_pool, MIN_REGIONS,
					sizeof(struct dm_region));
	if (ret) {
		vfree(rh->buckets);
		kfree(rh);
		rh = ERR_PTR(-ENOMEM);
	}

	return rh;
}