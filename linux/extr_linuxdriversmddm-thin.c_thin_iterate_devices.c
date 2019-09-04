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
struct thin_c {int /*<<< orphan*/  pool_dev; struct pool* pool; } ;
struct pool {int sectors_per_block; TYPE_1__* ti; } ;
struct dm_target {struct thin_c* private; } ;
typedef  int sector_t ;
typedef  int (* iterate_devices_callout_fn ) (struct dm_target*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  sector_div (int,int) ; 

__attribute__((used)) static int thin_iterate_devices(struct dm_target *ti,
				iterate_devices_callout_fn fn, void *data)
{
	sector_t blocks;
	struct thin_c *tc = ti->private;
	struct pool *pool = tc->pool;

	/*
	 * We can't call dm_pool_get_data_dev_size() since that blocks.  So
	 * we follow a more convoluted path through to the pool's target.
	 */
	if (!pool->ti)
		return 0;	/* nothing is bound */

	blocks = pool->ti->len;
	(void) sector_div(blocks, pool->sectors_per_block);
	if (blocks)
		return fn(ti, tc->pool_dev, 0, pool->sectors_per_block * blocks, data);

	return 0;
}