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
typedef  int u64 ;
struct queue_limits {int io_opt; } ;
struct dm_target {struct clone* private; } ;
struct clone {int region_size; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 
 int /*<<< orphan*/  blk_limits_io_min (struct queue_limits*,int) ; 
 int /*<<< orphan*/  blk_limits_io_opt (struct queue_limits*,int) ; 
 int /*<<< orphan*/  disable_passdown_if_not_supported (struct clone*) ; 
 scalar_t__ do_div (int,int) ; 
 int /*<<< orphan*/  set_discard_limits (struct clone*,struct queue_limits*) ; 

__attribute__((used)) static void clone_io_hints(struct dm_target *ti, struct queue_limits *limits)
{
	struct clone *clone = ti->private;
	u64 io_opt_sectors = limits->io_opt >> SECTOR_SHIFT;

	/*
	 * If the system-determined stacked limits are compatible with
	 * dm-clone's region size (io_opt is a factor) do not override them.
	 */
	if (io_opt_sectors < clone->region_size ||
	    do_div(io_opt_sectors, clone->region_size)) {
		blk_limits_io_min(limits, clone->region_size << SECTOR_SHIFT);
		blk_limits_io_opt(limits, clone->region_size << SECTOR_SHIFT);
	}

	disable_passdown_if_not_supported(clone);
	set_discard_limits(clone, limits);
}