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
struct dm_region_hash {int flush_failure; int /*<<< orphan*/  region_lock; int /*<<< orphan*/  hash_lock; struct dm_dirty_log* log; } ;
struct dm_region {scalar_t__ state; int /*<<< orphan*/  list; } ;
struct dm_dirty_log {TYPE_1__* type; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  region_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_region_sync ) (struct dm_dirty_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DM_RH_NOSYNC ; 
 scalar_t__ DM_RH_RECOVERING ; 
 scalar_t__ REQ_OP_DISCARD ; 
 int REQ_PREFLUSH ; 
 struct dm_region* __rh_find (struct dm_region_hash*,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_op (struct bio*) ; 
 int /*<<< orphan*/  complete_resync_work (struct dm_region*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_rh_bio_to_region (struct dm_region_hash*,struct bio*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct dm_dirty_log*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dm_rh_mark_nosync(struct dm_region_hash *rh, struct bio *bio)
{
	unsigned long flags;
	struct dm_dirty_log *log = rh->log;
	struct dm_region *reg;
	region_t region = dm_rh_bio_to_region(rh, bio);
	int recovering = 0;

	if (bio->bi_opf & REQ_PREFLUSH) {
		rh->flush_failure = 1;
		return;
	}

	if (bio_op(bio) == REQ_OP_DISCARD)
		return;

	/* We must inform the log that the sync count has changed. */
	log->type->set_region_sync(log, region, 0);

	read_lock(&rh->hash_lock);
	reg = __rh_find(rh, region);
	read_unlock(&rh->hash_lock);

	/* region hash entry should exist because write was in-flight */
	BUG_ON(!reg);
	BUG_ON(!list_empty(&reg->list));

	spin_lock_irqsave(&rh->region_lock, flags);
	/*
	 * Possible cases:
	 *   1) DM_RH_DIRTY
	 *   2) DM_RH_NOSYNC: was dirty, other preceding writes failed
	 *   3) DM_RH_RECOVERING: flushing pending writes
	 * Either case, the region should have not been connected to list.
	 */
	recovering = (reg->state == DM_RH_RECOVERING);
	reg->state = DM_RH_NOSYNC;
	BUG_ON(!list_empty(&reg->list));
	spin_unlock_irqrestore(&rh->region_lock, flags);

	if (recovering)
		complete_resync_work(reg, 0);
}