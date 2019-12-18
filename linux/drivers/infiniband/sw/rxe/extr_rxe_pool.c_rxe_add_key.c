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
typedef  int /*<<< orphan*/  u8 ;
struct rxe_pool_entry {struct rxe_pool* pool; } ;
struct rxe_pool {int key_offset; int /*<<< orphan*/  pool_lock; int /*<<< orphan*/  key_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  insert_key (struct rxe_pool*,struct rxe_pool_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rxe_add_key(void *arg, void *key)
{
	struct rxe_pool_entry *elem = arg;
	struct rxe_pool *pool = elem->pool;
	unsigned long flags;

	write_lock_irqsave(&pool->pool_lock, flags);
	memcpy((u8 *)elem + pool->key_offset, key, pool->key_size);
	insert_key(pool, elem);
	write_unlock_irqrestore(&pool->pool_lock, flags);
}