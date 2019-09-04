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
struct pool {scalar_t__ low_water_blocks; int low_water_triggered; TYPE_1__* ti; int /*<<< orphan*/  lock; int /*<<< orphan*/  pool_md; } ;
typedef  scalar_t__ dm_block_t ;
struct TYPE_2__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void check_low_water_mark(struct pool *pool, dm_block_t free_blocks)
{
	unsigned long flags;

	if (free_blocks <= pool->low_water_blocks && !pool->low_water_triggered) {
		DMWARN("%s: reached low water mark for data device: sending event.",
		       dm_device_name(pool->pool_md));
		spin_lock_irqsave(&pool->lock, flags);
		pool->low_water_triggered = true;
		spin_unlock_irqrestore(&pool->lock, flags);
		dm_table_event(pool->ti->table);
	}
}