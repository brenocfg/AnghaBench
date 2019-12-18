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
struct rxe_pool_entry {int /*<<< orphan*/  ref_cnt; struct rxe_pool* pool; } ;
struct rxe_pool {int flags; scalar_t__ state; scalar_t__ max_elem; TYPE_1__* rxe; int /*<<< orphan*/  num_elem; int /*<<< orphan*/  pool_lock; int /*<<< orphan*/  ref_cnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  ib_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int RXE_POOL_ATOMIC ; 
 scalar_t__ RXE_POOL_STATE_VALID ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_device_try_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep_if (int) ; 
 int /*<<< orphan*/  read_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  read_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rxe_pool_put (struct rxe_pool*) ; 

int rxe_add_to_pool(struct rxe_pool *pool, struct rxe_pool_entry *elem)
{
	unsigned long flags;

	might_sleep_if(!(pool->flags & RXE_POOL_ATOMIC));

	read_lock_irqsave(&pool->pool_lock, flags);
	if (pool->state != RXE_POOL_STATE_VALID) {
		read_unlock_irqrestore(&pool->pool_lock, flags);
		return -EINVAL;
	}
	kref_get(&pool->ref_cnt);
	read_unlock_irqrestore(&pool->pool_lock, flags);

	if (!ib_device_try_get(&pool->rxe->ib_dev))
		goto out_put_pool;

	if (atomic_inc_return(&pool->num_elem) > pool->max_elem)
		goto out_cnt;

	elem->pool = pool;
	kref_init(&elem->ref_cnt);

	return 0;

out_cnt:
	atomic_dec(&pool->num_elem);
	ib_device_put(&pool->rxe->ib_dev);
out_put_pool:
	rxe_pool_put(pool);
	return -EINVAL;
}