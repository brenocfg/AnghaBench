#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thin_c {scalar_t__ origin_dev; scalar_t__ pool_dev; int /*<<< orphan*/  td; TYPE_2__* pool; int /*<<< orphan*/  can_destroy; int /*<<< orphan*/  list; } ;
struct dm_target {struct thin_c* private; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pool_dec (TYPE_2__*) ; 
 int /*<<< orphan*/  dm_pool_close_thin_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_put_device (struct dm_target*,scalar_t__) ; 
 TYPE_1__ dm_thin_pool_table ; 
 int /*<<< orphan*/  kfree (struct thin_c*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  thin_put (struct thin_c*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thin_dtr(struct dm_target *ti)
{
	struct thin_c *tc = ti->private;
	unsigned long flags;

	spin_lock_irqsave(&tc->pool->lock, flags);
	list_del_rcu(&tc->list);
	spin_unlock_irqrestore(&tc->pool->lock, flags);
	synchronize_rcu();

	thin_put(tc);
	wait_for_completion(&tc->can_destroy);

	mutex_lock(&dm_thin_pool_table.mutex);

	__pool_dec(tc->pool);
	dm_pool_close_thin_device(tc->td);
	dm_put_device(ti, tc->pool_dev);
	if (tc->origin_dev)
		dm_put_device(ti, tc->origin_dev);
	kfree(tc);

	mutex_unlock(&dm_thin_pool_table.mutex);
}