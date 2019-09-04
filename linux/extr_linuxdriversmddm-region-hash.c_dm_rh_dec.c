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
struct dm_region_hash {int /*<<< orphan*/  context; int /*<<< orphan*/  (* wakeup_workers ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  region_lock; int /*<<< orphan*/  clean_regions; int /*<<< orphan*/  quiesced_regions; int /*<<< orphan*/  flush_failure; int /*<<< orphan*/  hash_lock; } ;
struct dm_region {scalar_t__ state; int /*<<< orphan*/  list; int /*<<< orphan*/  pending; } ;
typedef  int /*<<< orphan*/  region_t ;

/* Variables and functions */
 scalar_t__ DM_RH_CLEAN ; 
 scalar_t__ DM_RH_DIRTY ; 
 scalar_t__ DM_RH_NOSYNC ; 
 scalar_t__ DM_RH_RECOVERING ; 
 struct dm_region* __rh_lookup (struct dm_region_hash*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void dm_rh_dec(struct dm_region_hash *rh, region_t region)
{
	unsigned long flags;
	struct dm_region *reg;
	int should_wake = 0;

	read_lock(&rh->hash_lock);
	reg = __rh_lookup(rh, region);
	read_unlock(&rh->hash_lock);

	spin_lock_irqsave(&rh->region_lock, flags);
	if (atomic_dec_and_test(&reg->pending)) {
		/*
		 * There is no pending I/O for this region.
		 * We can move the region to corresponding list for next action.
		 * At this point, the region is not yet connected to any list.
		 *
		 * If the state is DM_RH_NOSYNC, the region should be kept off
		 * from clean list.
		 * The hash entry for DM_RH_NOSYNC will remain in memory
		 * until the region is recovered or the map is reloaded.
		 */

		/* do nothing for DM_RH_NOSYNC */
		if (unlikely(rh->flush_failure)) {
			/*
			 * If a write flush failed some time ago, we
			 * don't know whether or not this write made it
			 * to the disk, so we must resync the device.
			 */
			reg->state = DM_RH_NOSYNC;
		} else if (reg->state == DM_RH_RECOVERING) {
			list_add_tail(&reg->list, &rh->quiesced_regions);
		} else if (reg->state == DM_RH_DIRTY) {
			reg->state = DM_RH_CLEAN;
			list_add(&reg->list, &rh->clean_regions);
		}
		should_wake = 1;
	}
	spin_unlock_irqrestore(&rh->region_lock, flags);

	if (should_wake)
		rh->wakeup_workers(rh->context);
}