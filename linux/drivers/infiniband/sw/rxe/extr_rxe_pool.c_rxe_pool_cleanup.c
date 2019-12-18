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
struct rxe_pool {int /*<<< orphan*/  pool_lock; int /*<<< orphan*/  num_elem; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXE_POOL_STATE_INVALID ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pool_name (struct rxe_pool*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_pool_put (struct rxe_pool*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rxe_pool_cleanup(struct rxe_pool *pool)
{
	unsigned long flags;

	write_lock_irqsave(&pool->pool_lock, flags);
	pool->state = RXE_POOL_STATE_INVALID;
	if (atomic_read(&pool->num_elem) > 0)
		pr_warn("%s pool destroyed with unfree'd elem\n",
			pool_name(pool));
	write_unlock_irqrestore(&pool->pool_lock, flags);

	rxe_pool_put(pool);
}