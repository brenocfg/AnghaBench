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
struct dm_deferred_set {int current_entry; int /*<<< orphan*/  lock; struct dm_deferred_entry* entries; } ;
struct dm_deferred_entry {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct dm_deferred_entry *dm_deferred_entry_inc(struct dm_deferred_set *ds)
{
	unsigned long flags;
	struct dm_deferred_entry *entry;

	spin_lock_irqsave(&ds->lock, flags);
	entry = ds->entries + ds->current_entry;
	entry->count++;
	spin_unlock_irqrestore(&ds->lock, flags);

	return entry;
}