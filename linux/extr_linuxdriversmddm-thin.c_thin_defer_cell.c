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
struct thin_c {int /*<<< orphan*/  lock; int /*<<< orphan*/  deferred_cells; struct pool* pool; } ;
struct pool {int /*<<< orphan*/  throttle; } ;
struct dm_bio_prison_cell {int /*<<< orphan*/  user_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  throttle_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throttle_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_worker (struct pool*) ; 

__attribute__((used)) static void thin_defer_cell(struct thin_c *tc, struct dm_bio_prison_cell *cell)
{
	unsigned long flags;
	struct pool *pool = tc->pool;

	throttle_lock(&pool->throttle);
	spin_lock_irqsave(&tc->lock, flags);
	list_add_tail(&cell->user_list, &tc->deferred_cells);
	spin_unlock_irqrestore(&tc->lock, flags);
	throttle_unlock(&pool->throttle);

	wake_worker(pool);
}