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
struct thin_c {struct pool* pool; } ;
struct queue_limits {int discard_granularity; int max_discard_sectors; } ;
struct TYPE_2__ {int /*<<< orphan*/  discard_enabled; } ;
struct pool {int sectors_per_block; TYPE_1__ pf; } ;
struct dm_target {struct thin_c* private; } ;

/* Variables and functions */
 int SECTOR_SHIFT ; 

__attribute__((used)) static void thin_io_hints(struct dm_target *ti, struct queue_limits *limits)
{
	struct thin_c *tc = ti->private;
	struct pool *pool = tc->pool;

	if (!pool->pf.discard_enabled)
		return;

	limits->discard_granularity = pool->sectors_per_block << SECTOR_SHIFT;
	limits->max_discard_sectors = 2048 * 1024 * 16; /* 16G */
}