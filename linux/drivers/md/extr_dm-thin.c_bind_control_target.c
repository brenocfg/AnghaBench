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
struct TYPE_2__ {int mode; } ;
struct pool_c {int /*<<< orphan*/  low_water_blocks; TYPE_1__ adjusted_pf; } ;
struct pool {int /*<<< orphan*/  low_water_blocks; TYPE_1__ pf; struct dm_target* ti; } ;
struct dm_target {struct pool_c* private; } ;
typedef  enum pool_mode { ____Placeholder_pool_mode } pool_mode ;

/* Variables and functions */
 int get_pool_mode (struct pool*) ; 
 int /*<<< orphan*/  set_pool_mode (struct pool*,int) ; 

__attribute__((used)) static int bind_control_target(struct pool *pool, struct dm_target *ti)
{
	struct pool_c *pt = ti->private;

	/*
	 * We want to make sure that a pool in PM_FAIL mode is never upgraded.
	 */
	enum pool_mode old_mode = get_pool_mode(pool);
	enum pool_mode new_mode = pt->adjusted_pf.mode;

	/*
	 * Don't change the pool's mode until set_pool_mode() below.
	 * Otherwise the pool's process_* function pointers may
	 * not match the desired pool mode.
	 */
	pt->adjusted_pf.mode = old_mode;

	pool->ti = ti;
	pool->pf = pt->adjusted_pf;
	pool->low_water_blocks = pt->low_water_blocks;

	set_pool_mode(pool, new_mode);

	return 0;
}