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
struct dm_region_hash {int /*<<< orphan*/  recovery_count; int /*<<< orphan*/  context; int /*<<< orphan*/  (* wakeup_all_recovery_waiters ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  recovery_in_flight; int /*<<< orphan*/  (* dispatch_bios ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_2__* log; } ;
struct dm_region {int /*<<< orphan*/  delayed_bios; int /*<<< orphan*/  key; struct dm_region_hash* rh; } ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_region_sync ) (TYPE_2__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void complete_resync_work(struct dm_region *reg, int success)
{
	struct dm_region_hash *rh = reg->rh;

	rh->log->type->set_region_sync(rh->log, reg->key, success);

	/*
	 * Dispatch the bios before we call 'wake_up_all'.
	 * This is important because if we are suspending,
	 * we want to know that recovery is complete and
	 * the work queue is flushed.  If we wake_up_all
	 * before we dispatch_bios (queue bios and call wake()),
	 * then we risk suspending before the work queue
	 * has been properly flushed.
	 */
	rh->dispatch_bios(rh->context, &reg->delayed_bios);
	if (atomic_dec_and_test(&rh->recovery_in_flight))
		rh->wakeup_all_recovery_waiters(rh->context);
	up(&rh->recovery_count);
}