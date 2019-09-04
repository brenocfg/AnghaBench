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
struct queue_limits {int zoned; unsigned int chunk_sectors; } ;
struct dm_target {scalar_t__ len; scalar_t__ begin; TYPE_1__* type; } ;
struct dm_table {int /*<<< orphan*/  md; } ;
typedef  enum blk_zoned_model { ____Placeholder_blk_zoned_model } blk_zoned_model ;
struct TYPE_2__ {scalar_t__ (* iterate_devices ) (struct dm_target*,int /*<<< orphan*/ ,struct queue_limits*) ;int /*<<< orphan*/  (* io_hints ) (struct dm_target*,struct queue_limits*) ;} ;

/* Variables and functions */
 int BLK_ZONED_NONE ; 
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ,unsigned long long,unsigned long long) ; 
 int EINVAL ; 
 int /*<<< orphan*/  blk_set_stacking_limits (struct queue_limits*) ; 
 scalar_t__ blk_stack_limits (struct queue_limits*,struct queue_limits*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_area_is_invalid ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_set_device_limits ; 
 unsigned int dm_table_get_num_targets (struct dm_table*) ; 
 struct dm_target* dm_table_get_target (struct dm_table*,unsigned int) ; 
 scalar_t__ stub1 (struct dm_target*,int /*<<< orphan*/ ,struct queue_limits*) ; 
 int /*<<< orphan*/  stub2 (struct dm_target*,struct queue_limits*) ; 
 scalar_t__ stub3 (struct dm_target*,int /*<<< orphan*/ ,struct queue_limits*) ; 
 int validate_hardware_logical_block_alignment (struct dm_table*,struct queue_limits*) ; 
 scalar_t__ validate_hardware_zoned_model (struct dm_table*,int,unsigned int) ; 

int dm_calculate_queue_limits(struct dm_table *table,
			      struct queue_limits *limits)
{
	struct dm_target *ti;
	struct queue_limits ti_limits;
	unsigned i;
	enum blk_zoned_model zoned_model = BLK_ZONED_NONE;
	unsigned int zone_sectors = 0;

	blk_set_stacking_limits(limits);

	for (i = 0; i < dm_table_get_num_targets(table); i++) {
		blk_set_stacking_limits(&ti_limits);

		ti = dm_table_get_target(table, i);

		if (!ti->type->iterate_devices)
			goto combine_limits;

		/*
		 * Combine queue limits of all the devices this target uses.
		 */
		ti->type->iterate_devices(ti, dm_set_device_limits,
					  &ti_limits);

		if (zoned_model == BLK_ZONED_NONE && ti_limits.zoned != BLK_ZONED_NONE) {
			/*
			 * After stacking all limits, validate all devices
			 * in table support this zoned model and zone sectors.
			 */
			zoned_model = ti_limits.zoned;
			zone_sectors = ti_limits.chunk_sectors;
		}

		/* Set I/O hints portion of queue limits */
		if (ti->type->io_hints)
			ti->type->io_hints(ti, &ti_limits);

		/*
		 * Check each device area is consistent with the target's
		 * overall queue limits.
		 */
		if (ti->type->iterate_devices(ti, device_area_is_invalid,
					      &ti_limits))
			return -EINVAL;

combine_limits:
		/*
		 * Merge this target's queue limits into the overall limits
		 * for the table.
		 */
		if (blk_stack_limits(limits, &ti_limits, 0) < 0)
			DMWARN("%s: adding target device "
			       "(start sect %llu len %llu) "
			       "caused an alignment inconsistency",
			       dm_device_name(table->md),
			       (unsigned long long) ti->begin,
			       (unsigned long long) ti->len);

		/*
		 * FIXME: this should likely be moved to blk_stack_limits(), would
		 * also eliminate limits->zoned stacking hack in dm_set_device_limits()
		 */
		if (limits->zoned == BLK_ZONED_NONE && ti_limits.zoned != BLK_ZONED_NONE) {
			/*
			 * By default, the stacked limits zoned model is set to
			 * BLK_ZONED_NONE in blk_set_stacking_limits(). Update
			 * this model using the first target model reported
			 * that is not BLK_ZONED_NONE. This will be either the
			 * first target device zoned model or the model reported
			 * by the target .io_hints.
			 */
			limits->zoned = ti_limits.zoned;
		}
	}

	/*
	 * Verify that the zoned model and zone sectors, as determined before
	 * any .io_hints override, are the same across all devices in the table.
	 * - this is especially relevant if .io_hints is emulating a disk-managed
	 *   zoned model (aka BLK_ZONED_NONE) on host-managed zoned block devices.
	 * BUT...
	 */
	if (limits->zoned != BLK_ZONED_NONE) {
		/*
		 * ...IF the above limits stacking determined a zoned model
		 * validate that all of the table's devices conform to it.
		 */
		zoned_model = limits->zoned;
		zone_sectors = limits->chunk_sectors;
	}
	if (validate_hardware_zoned_model(table, zoned_model, zone_sectors))
		return -EINVAL;

	return validate_hardware_logical_block_alignment(table, limits);
}