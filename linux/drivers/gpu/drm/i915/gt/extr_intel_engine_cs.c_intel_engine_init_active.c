#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dep_map; } ;
struct TYPE_4__ {TYPE_2__ lock; int /*<<< orphan*/  requests; } ;
struct intel_engine_cs {TYPE_1__ active; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  lock_map_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_map_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_set_subclass (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_init (TYPE_2__*) ; 

void
intel_engine_init_active(struct intel_engine_cs *engine, unsigned int subclass)
{
	INIT_LIST_HEAD(&engine->active.requests);

	spin_lock_init(&engine->active.lock);
	lockdep_set_subclass(&engine->active.lock, subclass);

	/*
	 * Due to an interesting quirk in lockdep's internal debug tracking,
	 * after setting a subclass we must ensure the lock is used. Otherwise,
	 * nr_unused_locks is incremented once too often.
	 */
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	local_irq_disable();
	lock_map_acquire(&engine->active.lock.dep_map);
	lock_map_release(&engine->active.lock.dep_map);
	local_irq_enable();
#endif
}