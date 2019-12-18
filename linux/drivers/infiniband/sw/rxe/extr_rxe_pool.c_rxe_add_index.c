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
struct rxe_pool_entry {int /*<<< orphan*/  index; struct rxe_pool* pool; } ;
struct rxe_pool {int /*<<< orphan*/  pool_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  alloc_index (struct rxe_pool*) ; 
 int /*<<< orphan*/  insert_index (struct rxe_pool*,struct rxe_pool_entry*) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rxe_add_index(void *arg)
{
	struct rxe_pool_entry *elem = arg;
	struct rxe_pool *pool = elem->pool;
	unsigned long flags;

	write_lock_irqsave(&pool->pool_lock, flags);
	elem->index = alloc_index(pool);
	insert_index(pool, elem);
	write_unlock_irqrestore(&pool->pool_lock, flags);
}