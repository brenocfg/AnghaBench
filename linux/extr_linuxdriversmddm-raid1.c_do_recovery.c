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
struct mirror_set {int in_sync; scalar_t__ nr_regions; TYPE_1__* ti; int /*<<< orphan*/  rh; } ;
struct dm_region {int dummy; } ;
struct dm_dirty_log {TYPE_2__* type; } ;
struct TYPE_4__ {scalar_t__ (* get_sync_count ) (struct dm_dirty_log*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  table; } ;

/* Variables and functions */
 struct dm_dirty_log* dm_rh_dirty_log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_rh_recovery_prepare (int /*<<< orphan*/ ) ; 
 struct dm_region* dm_rh_recovery_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_table_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recover (struct mirror_set*,struct dm_region*) ; 
 int /*<<< orphan*/  reset_ms_flags (struct mirror_set*) ; 
 scalar_t__ stub1 (struct dm_dirty_log*) ; 

__attribute__((used)) static void do_recovery(struct mirror_set *ms)
{
	struct dm_region *reg;
	struct dm_dirty_log *log = dm_rh_dirty_log(ms->rh);

	/*
	 * Start quiescing some regions.
	 */
	dm_rh_recovery_prepare(ms->rh);

	/*
	 * Copy any already quiesced regions.
	 */
	while ((reg = dm_rh_recovery_start(ms->rh)))
		recover(ms, reg);

	/*
	 * Update the in sync flag.
	 */
	if (!ms->in_sync &&
	    (log->type->get_sync_count(log) == ms->nr_regions)) {
		/* the sync is complete */
		dm_table_event(ms->ti->table);
		ms->in_sync = 1;
		reset_ms_flags(ms);
	}
}