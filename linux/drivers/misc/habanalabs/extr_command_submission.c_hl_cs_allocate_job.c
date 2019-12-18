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
struct hl_device {int dummy; } ;
struct hl_cs_job {int ext_queue; int /*<<< orphan*/  finish_work; int /*<<< orphan*/  userptr_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  job_wq_completion ; 
 struct hl_cs_job* kzalloc (int,int /*<<< orphan*/ ) ; 

struct hl_cs_job *hl_cs_allocate_job(struct hl_device *hdev, bool ext_queue)
{
	struct hl_cs_job *job;

	job = kzalloc(sizeof(*job), GFP_ATOMIC);
	if (!job)
		return NULL;

	job->ext_queue = ext_queue;

	if (job->ext_queue) {
		INIT_LIST_HEAD(&job->userptr_list);
		INIT_WORK(&job->finish_work, job_wq_completion);
	}

	return job;
}