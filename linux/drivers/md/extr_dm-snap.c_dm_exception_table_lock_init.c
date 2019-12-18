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
struct dm_exception_table {int /*<<< orphan*/ * table; } ;
struct dm_snapshot {struct dm_exception_table pending; struct dm_exception_table complete; } ;
struct dm_exception_table_lock {int /*<<< orphan*/ * pending_slot; int /*<<< orphan*/ * complete_slot; } ;
typedef  int /*<<< orphan*/  chunk_t ;

/* Variables and functions */
 size_t exception_hash (struct dm_exception_table*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_exception_table_lock_init(struct dm_snapshot *s, chunk_t chunk,
					 struct dm_exception_table_lock *lock)
{
	struct dm_exception_table *complete = &s->complete;
	struct dm_exception_table *pending = &s->pending;

	lock->complete_slot = &complete->table[exception_hash(complete, chunk)];
	lock->pending_slot = &pending->table[exception_hash(pending, chunk)];
}