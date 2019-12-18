#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dm_region_hash {int /*<<< orphan*/  region_lock; int /*<<< orphan*/  quiesced_regions; int /*<<< orphan*/  hash_lock; TYPE_2__* log; } ;
struct dm_region {int /*<<< orphan*/  list; int /*<<< orphan*/  pending; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  region_t ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int (* get_resync_work ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DM_RH_RECOVERING ; 
 struct dm_region* __rh_find (struct dm_region_hash*,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __rh_recovery_prepare(struct dm_region_hash *rh)
{
	int r;
	region_t region;
	struct dm_region *reg;

	/*
	 * Ask the dirty log what's next.
	 */
	r = rh->log->type->get_resync_work(rh->log, &region);
	if (r <= 0)
		return r;

	/*
	 * Get this region, and start it quiescing by setting the
	 * recovering flag.
	 */
	read_lock(&rh->hash_lock);
	reg = __rh_find(rh, region);
	read_unlock(&rh->hash_lock);

	spin_lock_irq(&rh->region_lock);
	reg->state = DM_RH_RECOVERING;

	/* Already quiesced ? */
	if (atomic_read(&reg->pending))
		list_del_init(&reg->list);
	else
		list_move(&reg->list, &rh->quiesced_regions);

	spin_unlock_irq(&rh->region_lock);

	return 1;
}