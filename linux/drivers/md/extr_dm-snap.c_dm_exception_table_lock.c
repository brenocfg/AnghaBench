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
struct dm_exception_table_lock {int /*<<< orphan*/  pending_slot; int /*<<< orphan*/  complete_slot; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_bl_lock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_exception_table_lock(struct dm_exception_table_lock *lock)
{
	hlist_bl_lock(lock->complete_slot);
	hlist_bl_lock(lock->pending_slot);
}