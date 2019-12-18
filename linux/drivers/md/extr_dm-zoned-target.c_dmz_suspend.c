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
struct dmz_target {int /*<<< orphan*/  flush_work; int /*<<< orphan*/  reclaim; int /*<<< orphan*/  chunk_wq; } ;
struct dm_target {struct dmz_target* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmz_suspend_reclaim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dmz_suspend(struct dm_target *ti)
{
	struct dmz_target *dmz = ti->private;

	flush_workqueue(dmz->chunk_wq);
	dmz_suspend_reclaim(dmz->reclaim);
	cancel_delayed_work_sync(&dmz->flush_work);
}