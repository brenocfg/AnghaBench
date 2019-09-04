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
struct queue_limits {unsigned int max_discard_sectors; unsigned int max_hw_discard_sectors; unsigned int max_write_zeroes_sectors; unsigned int chunk_sectors; unsigned int max_sectors; int /*<<< orphan*/  zoned; void* discard_granularity; void* discard_alignment; void* physical_block_size; void* logical_block_size; } ;
struct dmz_target {TYPE_1__* dev; } ;
struct dm_target {struct dmz_target* private; } ;
struct TYPE_2__ {unsigned int zone_nr_sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_ZONED_NONE ; 
 void* DMZ_BLOCK_SIZE ; 
 int /*<<< orphan*/  blk_limits_io_min (struct queue_limits*,void*) ; 
 int /*<<< orphan*/  blk_limits_io_opt (struct queue_limits*,void*) ; 

__attribute__((used)) static void dmz_io_hints(struct dm_target *ti, struct queue_limits *limits)
{
	struct dmz_target *dmz = ti->private;
	unsigned int chunk_sectors = dmz->dev->zone_nr_sectors;

	limits->logical_block_size = DMZ_BLOCK_SIZE;
	limits->physical_block_size = DMZ_BLOCK_SIZE;

	blk_limits_io_min(limits, DMZ_BLOCK_SIZE);
	blk_limits_io_opt(limits, DMZ_BLOCK_SIZE);

	limits->discard_alignment = DMZ_BLOCK_SIZE;
	limits->discard_granularity = DMZ_BLOCK_SIZE;
	limits->max_discard_sectors = chunk_sectors;
	limits->max_hw_discard_sectors = chunk_sectors;
	limits->max_write_zeroes_sectors = chunk_sectors;

	/* FS hint to try to align to the device zone size */
	limits->chunk_sectors = chunk_sectors;
	limits->max_sectors = chunk_sectors;

	/* We are exposing a drive-managed zoned block device */
	limits->zoned = BLK_ZONED_NONE;
}