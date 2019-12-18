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
struct queue_limits {int discard_granularity; int /*<<< orphan*/  max_discard_segments; int /*<<< orphan*/  discard_misaligned; int /*<<< orphan*/  discard_alignment; int /*<<< orphan*/  max_hw_discard_sectors; int /*<<< orphan*/  max_discard_sectors; } ;
struct clone {int region_size; int /*<<< orphan*/  flags; TYPE_1__* dest_dev; } ;
struct block_device {int dummy; } ;
struct TYPE_4__ {struct queue_limits limits; } ;
struct TYPE_3__ {struct block_device* bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_CLONE_DISCARD_PASSDOWN ; 
 int SECTOR_SHIFT ; 
 int UINT_MAX ; 
 TYPE_2__* bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  round_down (int,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_discard_limits(struct clone *clone, struct queue_limits *limits)
{
	struct block_device *dest_bdev = clone->dest_dev->bdev;
	struct queue_limits *dest_limits = &bdev_get_queue(dest_bdev)->limits;

	if (!test_bit(DM_CLONE_DISCARD_PASSDOWN, &clone->flags)) {
		/* No passdown is done so we set our own virtual limits */
		limits->discard_granularity = clone->region_size << SECTOR_SHIFT;
		limits->max_discard_sectors = round_down(UINT_MAX >> SECTOR_SHIFT, clone->region_size);
		return;
	}

	/*
	 * clone_iterate_devices() is stacking both the source and destination
	 * device limits but discards aren't passed to the source device, so
	 * inherit destination's limits.
	 */
	limits->max_discard_sectors = dest_limits->max_discard_sectors;
	limits->max_hw_discard_sectors = dest_limits->max_hw_discard_sectors;
	limits->discard_granularity = dest_limits->discard_granularity;
	limits->discard_alignment = dest_limits->discard_alignment;
	limits->discard_misaligned = dest_limits->discard_misaligned;
	limits->max_discard_segments = dest_limits->max_discard_segments;
}