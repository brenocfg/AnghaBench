#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dm_io_region {int sector; int count; int /*<<< orphan*/  bdev; } ;
struct dm_cache_migration {int /*<<< orphan*/  k; TYPE_3__* op; struct cache* cache; } ;
struct cache {int sectors_per_block; int /*<<< orphan*/  copier; TYPE_2__* cache_dev; TYPE_1__* origin_dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  cblock; int /*<<< orphan*/  oblock; } ;
struct TYPE_5__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_complete ; 
 int /*<<< orphan*/  dm_kcopyd_copy (int /*<<< orphan*/ ,struct dm_io_region*,int,struct dm_io_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int from_cblock (int /*<<< orphan*/ ) ; 
 int from_oblock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy(struct dm_cache_migration *mg, bool promote)
{
	struct dm_io_region o_region, c_region;
	struct cache *cache = mg->cache;

	o_region.bdev = cache->origin_dev->bdev;
	o_region.sector = from_oblock(mg->op->oblock) * cache->sectors_per_block;
	o_region.count = cache->sectors_per_block;

	c_region.bdev = cache->cache_dev->bdev;
	c_region.sector = from_cblock(mg->op->cblock) * cache->sectors_per_block;
	c_region.count = cache->sectors_per_block;

	if (promote)
		dm_kcopyd_copy(cache->copier, &o_region, 1, &c_region, 0, copy_complete, &mg->k);
	else
		dm_kcopyd_copy(cache->copier, &c_region, 1, &o_region, 0, copy_complete, &mg->k);
}