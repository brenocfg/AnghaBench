#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct dm_target {struct cache* private; } ;
struct TYPE_8__ {int /*<<< orphan*/  promotion; int /*<<< orphan*/  demotion; int /*<<< orphan*/  write_miss; int /*<<< orphan*/  write_hit; int /*<<< orphan*/  read_miss; int /*<<< orphan*/  read_hit; } ;
struct cache {int /*<<< orphan*/  nr_ctr_args; int /*<<< orphan*/ * ctr_args; TYPE_7__* origin_dev; TYPE_5__* cache_dev; TYPE_3__* metadata_dev; int /*<<< orphan*/  cmd; int /*<<< orphan*/  policy; scalar_t__ migration_threshold; int /*<<< orphan*/  nr_dirty; TYPE_1__ stats; int /*<<< orphan*/  cache_size; scalar_t__ sectors_per_block; } ;
typedef  int status_type_t ;
typedef  unsigned int ssize_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;
typedef  scalar_t__ dm_block_t ;
struct TYPE_14__ {TYPE_6__* bdev; } ;
struct TYPE_13__ {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_12__ {TYPE_4__* bdev; } ;
struct TYPE_11__ {int /*<<< orphan*/  bd_dev; } ;
struct TYPE_10__ {TYPE_2__* bdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  bd_dev; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  CM_FAIL ; 
 int /*<<< orphan*/  CM_READ_ONLY ; 
 int /*<<< orphan*/  DMEMIT (char*,...) ; 
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DM_CACHE_METADATA_BLOCK_SIZE ; 
 unsigned int DM_STATUS_NOFLUSH_FLAG ; 
#define  STATUSTYPE_INFO 129 
#define  STATUSTYPE_TABLE 128 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 int /*<<< orphan*/  commit (struct cache*,int) ; 
 int dm_cache_get_free_metadata_block_count (int /*<<< orphan*/ ,scalar_t__*) ; 
 int dm_cache_get_metadata_dev_size (int /*<<< orphan*/ ,scalar_t__*) ; 
 int dm_cache_metadata_needs_check (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dm_cache_policy_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_suspended (struct dm_target*) ; 
 int /*<<< orphan*/  emit_flags (struct cache*,char*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  format_dev_t (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ from_cblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cache_mode (struct cache*) ; 
 int policy_emit_config_values (int /*<<< orphan*/ ,char*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  policy_residency (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cache_status(struct dm_target *ti, status_type_t type,
			 unsigned status_flags, char *result, unsigned maxlen)
{
	int r = 0;
	unsigned i;
	ssize_t sz = 0;
	dm_block_t nr_free_blocks_metadata = 0;
	dm_block_t nr_blocks_metadata = 0;
	char buf[BDEVNAME_SIZE];
	struct cache *cache = ti->private;
	dm_cblock_t residency;
	bool needs_check;

	switch (type) {
	case STATUSTYPE_INFO:
		if (get_cache_mode(cache) == CM_FAIL) {
			DMEMIT("Fail");
			break;
		}

		/* Commit to ensure statistics aren't out-of-date */
		if (!(status_flags & DM_STATUS_NOFLUSH_FLAG) && !dm_suspended(ti))
			(void) commit(cache, false);

		r = dm_cache_get_free_metadata_block_count(cache->cmd, &nr_free_blocks_metadata);
		if (r) {
			DMERR("%s: dm_cache_get_free_metadata_block_count returned %d",
			      cache_device_name(cache), r);
			goto err;
		}

		r = dm_cache_get_metadata_dev_size(cache->cmd, &nr_blocks_metadata);
		if (r) {
			DMERR("%s: dm_cache_get_metadata_dev_size returned %d",
			      cache_device_name(cache), r);
			goto err;
		}

		residency = policy_residency(cache->policy);

		DMEMIT("%u %llu/%llu %llu %llu/%llu %u %u %u %u %u %u %lu ",
		       (unsigned)DM_CACHE_METADATA_BLOCK_SIZE,
		       (unsigned long long)(nr_blocks_metadata - nr_free_blocks_metadata),
		       (unsigned long long)nr_blocks_metadata,
		       (unsigned long long)cache->sectors_per_block,
		       (unsigned long long) from_cblock(residency),
		       (unsigned long long) from_cblock(cache->cache_size),
		       (unsigned) atomic_read(&cache->stats.read_hit),
		       (unsigned) atomic_read(&cache->stats.read_miss),
		       (unsigned) atomic_read(&cache->stats.write_hit),
		       (unsigned) atomic_read(&cache->stats.write_miss),
		       (unsigned) atomic_read(&cache->stats.demotion),
		       (unsigned) atomic_read(&cache->stats.promotion),
		       (unsigned long) atomic_read(&cache->nr_dirty));

		emit_flags(cache, result, maxlen, &sz);

		DMEMIT("2 migration_threshold %llu ", (unsigned long long) cache->migration_threshold);

		DMEMIT("%s ", dm_cache_policy_get_name(cache->policy));
		if (sz < maxlen) {
			r = policy_emit_config_values(cache->policy, result, maxlen, &sz);
			if (r)
				DMERR("%s: policy_emit_config_values returned %d",
				      cache_device_name(cache), r);
		}

		if (get_cache_mode(cache) == CM_READ_ONLY)
			DMEMIT("ro ");
		else
			DMEMIT("rw ");

		r = dm_cache_metadata_needs_check(cache->cmd, &needs_check);

		if (r || needs_check)
			DMEMIT("needs_check ");
		else
			DMEMIT("- ");

		break;

	case STATUSTYPE_TABLE:
		format_dev_t(buf, cache->metadata_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);
		format_dev_t(buf, cache->cache_dev->bdev->bd_dev);
		DMEMIT("%s ", buf);
		format_dev_t(buf, cache->origin_dev->bdev->bd_dev);
		DMEMIT("%s", buf);

		for (i = 0; i < cache->nr_ctr_args - 1; i++)
			DMEMIT(" %s", cache->ctr_args[i]);
		if (cache->nr_ctr_args)
			DMEMIT(" %s", cache->ctr_args[cache->nr_ctr_args - 1]);
	}

	return;

err:
	DMEMIT("Error");
}