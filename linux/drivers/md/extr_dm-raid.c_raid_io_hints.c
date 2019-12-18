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
struct TYPE_2__ {int /*<<< orphan*/  chunk_sectors; } ;
struct raid_set {TYPE_1__ md; } ;
struct queue_limits {unsigned int discard_granularity; int /*<<< orphan*/  max_discard_sectors; } ;
struct dm_target {struct raid_set* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_limits_io_min (struct queue_limits*,unsigned int) ; 
 int /*<<< orphan*/  blk_limits_io_opt (struct queue_limits*,unsigned int) ; 
 unsigned int mddev_data_stripes (struct raid_set*) ; 
 scalar_t__ rs_is_raid1 (struct raid_set*) ; 
 scalar_t__ rs_is_raid10 (struct raid_set*) ; 
 unsigned int to_bytes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raid_io_hints(struct dm_target *ti, struct queue_limits *limits)
{
	struct raid_set *rs = ti->private;
	unsigned int chunk_size_bytes = to_bytes(rs->md.chunk_sectors);

	blk_limits_io_min(limits, chunk_size_bytes);
	blk_limits_io_opt(limits, chunk_size_bytes * mddev_data_stripes(rs));

	/*
	 * RAID1 and RAID10 personalities require bio splitting,
	 * RAID0/4/5/6 don't and process large discard bios properly.
	 */
	if (rs_is_raid1(rs) || rs_is_raid10(rs)) {
		limits->discard_granularity = chunk_size_bytes;
		limits->max_discard_sectors = rs->md.chunk_sectors;
	}
}