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

/* Variables and functions */
 int IWPM_MAPINFO_HASH_SIZE ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iwpm_hash_bucket ; 
 int /*<<< orphan*/  iwpm_mapinfo_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int iwpm_mapinfo_available(void)
{
	unsigned long flags;
	int full_bucket = 0, i = 0;

	spin_lock_irqsave(&iwpm_mapinfo_lock, flags);
	if (iwpm_hash_bucket) {
		for (i = 0; i < IWPM_MAPINFO_HASH_SIZE; i++) {
			if (!hlist_empty(&iwpm_hash_bucket[i])) {
				full_bucket = 1;
				break;
			}
		}
	}
	spin_unlock_irqrestore(&iwpm_mapinfo_lock, flags);
	return full_bucket;
}