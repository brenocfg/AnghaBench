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
struct queue_limits {int dummy; } ;
struct dm_target {struct raid_set* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_limits_io_min (struct queue_limits*,unsigned int) ; 
 int /*<<< orphan*/  blk_limits_io_opt (struct queue_limits*,unsigned int) ; 
 unsigned int mddev_data_stripes (struct raid_set*) ; 
 unsigned int to_bytes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raid_io_hints(struct dm_target *ti, struct queue_limits *limits)
{
	struct raid_set *rs = ti->private;
	unsigned int chunk_size = to_bytes(rs->md.chunk_sectors);

	blk_limits_io_min(limits, chunk_size);
	blk_limits_io_opt(limits, chunk_size * mddev_data_stripes(rs));
}