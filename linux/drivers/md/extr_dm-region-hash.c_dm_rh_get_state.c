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
struct dm_region_hash {TYPE_2__* log; int /*<<< orphan*/  hash_lock; } ;
struct dm_region {int state; } ;
typedef  int /*<<< orphan*/  region_t ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int (* in_sync ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int DM_RH_CLEAN ; 
 int DM_RH_NOSYNC ; 
 struct dm_region* __rh_lookup (struct dm_region_hash*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int dm_rh_get_state(struct dm_region_hash *rh, region_t region, int may_block)
{
	int r;
	struct dm_region *reg;

	read_lock(&rh->hash_lock);
	reg = __rh_lookup(rh, region);
	read_unlock(&rh->hash_lock);

	if (reg)
		return reg->state;

	/*
	 * The region wasn't in the hash, so we fall back to the
	 * dirty log.
	 */
	r = rh->log->type->in_sync(rh->log, region, may_block);

	/*
	 * Any error from the dirty log (eg. -EWOULDBLOCK) gets
	 * taken as a DM_RH_NOSYNC
	 */
	return r == 1 ? DM_RH_CLEAN : DM_RH_NOSYNC;
}