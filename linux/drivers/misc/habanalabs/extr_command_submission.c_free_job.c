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
struct hl_device {int dummy; } ;
struct hl_cs_job {scalar_t__ ext_queue; int /*<<< orphan*/  cs_node; TYPE_1__* patched_cb; int /*<<< orphan*/  userptr_list; struct hl_cs* cs; } ;
struct hl_cs {int /*<<< orphan*/  job_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cs_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs_put (struct hl_cs*) ; 
 int /*<<< orphan*/  hl_cb_put (TYPE_1__*) ; 
 int /*<<< orphan*/  hl_debugfs_remove_job (struct hl_device*,struct hl_cs_job*) ; 
 int /*<<< orphan*/  hl_userptr_delete_list (struct hl_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hl_cs_job*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_job(struct hl_device *hdev, struct hl_cs_job *job)
{
	struct hl_cs *cs = job->cs;

	if (job->ext_queue) {
		hl_userptr_delete_list(hdev, &job->userptr_list);

		/*
		 * We might arrive here from rollback and patched CB wasn't
		 * created, so we need to check it's not NULL
		 */
		if (job->patched_cb) {
			spin_lock(&job->patched_cb->lock);
			job->patched_cb->cs_cnt--;
			spin_unlock(&job->patched_cb->lock);

			hl_cb_put(job->patched_cb);
		}
	}

	/*
	 * This is the only place where there can be multiple threads
	 * modifying the list at the same time
	 */
	spin_lock(&cs->job_lock);
	list_del(&job->cs_node);
	spin_unlock(&cs->job_lock);

	hl_debugfs_remove_job(hdev, job);

	if (job->ext_queue)
		cs_put(cs);

	kfree(job);
}