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
struct stripe_c {unsigned int chunk_size; unsigned int stripes; } ;
struct queue_limits {int dummy; } ;
struct dm_target {struct stripe_c* private; } ;

/* Variables and functions */
 unsigned int SECTOR_SHIFT ; 
 int /*<<< orphan*/  blk_limits_io_min (struct queue_limits*,unsigned int) ; 
 int /*<<< orphan*/  blk_limits_io_opt (struct queue_limits*,unsigned int) ; 

__attribute__((used)) static void stripe_io_hints(struct dm_target *ti,
			    struct queue_limits *limits)
{
	struct stripe_c *sc = ti->private;
	unsigned chunk_size = sc->chunk_size << SECTOR_SHIFT;

	blk_limits_io_min(limits, chunk_size);
	blk_limits_io_opt(limits, chunk_size * sc->stripes);
}