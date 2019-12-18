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
struct queue_limits {int discard_granularity; int /*<<< orphan*/  discard_misaligned; int /*<<< orphan*/  discard_alignment; int /*<<< orphan*/  max_hw_discard_sectors; int /*<<< orphan*/  max_discard_sectors; } ;
struct TYPE_5__ {int /*<<< orphan*/  discard_passdown; } ;
struct cache {int discard_block_size; int /*<<< orphan*/  origin_sectors; TYPE_2__ features; TYPE_1__* origin_dev; } ;
struct block_device {int dummy; } ;
struct TYPE_6__ {struct queue_limits limits; } ;
struct TYPE_4__ {struct block_device* bdev; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 TYPE_3__* bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sector_t ; 

__attribute__((used)) static void set_discard_limits(struct cache *cache, struct queue_limits *limits)
{
	struct block_device *origin_bdev = cache->origin_dev->bdev;
	struct queue_limits *origin_limits = &bdev_get_queue(origin_bdev)->limits;

	if (!cache->features.discard_passdown) {
		/* No passdown is done so setting own virtual limits */
		limits->max_discard_sectors = min_t(sector_t, cache->discard_block_size * 1024,
						    cache->origin_sectors);
		limits->discard_granularity = cache->discard_block_size << SECTOR_SHIFT;
		return;
	}

	/*
	 * cache_iterate_devices() is stacking both origin and fast device limits
	 * but discards aren't passed to fast device, so inherit origin's limits.
	 */
	limits->max_discard_sectors = origin_limits->max_discard_sectors;
	limits->max_hw_discard_sectors = origin_limits->max_hw_discard_sectors;
	limits->discard_granularity = origin_limits->discard_granularity;
	limits->discard_alignment = origin_limits->discard_alignment;
	limits->discard_misaligned = origin_limits->discard_misaligned;
}