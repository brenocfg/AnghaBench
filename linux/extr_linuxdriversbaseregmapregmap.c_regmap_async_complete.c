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
struct regmap {int async_ret; int /*<<< orphan*/  async_lock; int /*<<< orphan*/  async_waitq; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  async_write; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_async_is_done (struct regmap*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_regmap_async_complete_done (struct regmap*) ; 
 int /*<<< orphan*/  trace_regmap_async_complete_start (struct regmap*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int regmap_async_complete(struct regmap *map)
{
	unsigned long flags;
	int ret;

	/* Nothing to do with no async support */
	if (!map->bus || !map->bus->async_write)
		return 0;

	trace_regmap_async_complete_start(map);

	wait_event(map->async_waitq, regmap_async_is_done(map));

	spin_lock_irqsave(&map->async_lock, flags);
	ret = map->async_ret;
	map->async_ret = 0;
	spin_unlock_irqrestore(&map->async_lock, flags);

	trace_regmap_async_complete_done(map);

	return ret;
}