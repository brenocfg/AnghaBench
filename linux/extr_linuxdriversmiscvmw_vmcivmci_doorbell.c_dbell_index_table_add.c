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
typedef  int u32 ;
struct dbell_entry {int idx; int /*<<< orphan*/  node; int /*<<< orphan*/  resource; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int VMCI_DOORBELL_HASH (int) ; 
 int /*<<< orphan*/  dbell_index_table_find (int) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int last_notify_idx_released ; 
 int last_notify_idx_reserved ; 
 int max_notify_idx ; 
 int notify_idx_count ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 TYPE_1__ vmci_doorbell_it ; 
 int /*<<< orphan*/  vmci_resource_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dbell_index_table_add(struct dbell_entry *entry)
{
	u32 bucket;
	u32 new_notify_idx;

	vmci_resource_get(&entry->resource);

	spin_lock_bh(&vmci_doorbell_it.lock);

	/*
	 * Below we try to allocate an index in the notification
	 * bitmap with "not too much" sharing between resources. If we
	 * use less that the full bitmap, we either add to the end if
	 * there are no unused flags within the currently used area,
	 * or we search for unused ones. If we use the full bitmap, we
	 * allocate the index round robin.
	 */
	if (max_notify_idx < PAGE_SIZE || notify_idx_count < PAGE_SIZE) {
		if (last_notify_idx_released < max_notify_idx &&
		    !dbell_index_table_find(last_notify_idx_released)) {
			new_notify_idx = last_notify_idx_released;
			last_notify_idx_released = PAGE_SIZE;
		} else {
			bool reused = false;
			new_notify_idx = last_notify_idx_reserved;
			if (notify_idx_count + 1 < max_notify_idx) {
				do {
					if (!dbell_index_table_find
					    (new_notify_idx)) {
						reused = true;
						break;
					}
					new_notify_idx = (new_notify_idx + 1) %
					    max_notify_idx;
				} while (new_notify_idx !=
					 last_notify_idx_released);
			}
			if (!reused) {
				new_notify_idx = max_notify_idx;
				max_notify_idx++;
			}
		}
	} else {
		new_notify_idx = (last_notify_idx_reserved + 1) % PAGE_SIZE;
	}

	last_notify_idx_reserved = new_notify_idx;
	notify_idx_count++;

	entry->idx = new_notify_idx;
	bucket = VMCI_DOORBELL_HASH(entry->idx);
	hlist_add_head(&entry->node, &vmci_doorbell_it.entries[bucket]);

	spin_unlock_bh(&vmci_doorbell_it.lock);
}