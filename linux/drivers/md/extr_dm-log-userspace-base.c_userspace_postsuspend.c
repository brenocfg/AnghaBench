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
struct log_c {int /*<<< orphan*/  luid; int /*<<< orphan*/  uuid; int /*<<< orphan*/  flush_log_work; int /*<<< orphan*/  sched_flush; scalar_t__ integrated_flush; } ;
struct dm_dirty_log {struct log_c* context; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM_ULOG_POSTSUSPEND ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int dm_consult_userspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int userspace_postsuspend(struct dm_dirty_log *log)
{
	int r;
	struct log_c *lc = log->context;

	/*
	 * Run planned flush earlier.
	 */
	if (lc->integrated_flush && atomic_read(&lc->sched_flush))
		flush_delayed_work(&lc->flush_log_work);

	r = dm_consult_userspace(lc->uuid, lc->luid, DM_ULOG_POSTSUSPEND,
				 NULL, 0, NULL, NULL);

	return r;
}