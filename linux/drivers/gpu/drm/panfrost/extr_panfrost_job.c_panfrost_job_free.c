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
struct panfrost_job {int dummy; } ;
struct drm_sched_job {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_sched_job_cleanup (struct drm_sched_job*) ; 
 int /*<<< orphan*/  panfrost_job_put (struct panfrost_job*) ; 
 struct panfrost_job* to_panfrost_job (struct drm_sched_job*) ; 

__attribute__((used)) static void panfrost_job_free(struct drm_sched_job *sched_job)
{
	struct panfrost_job *job = to_panfrost_job(sched_job);

	drm_sched_job_cleanup(sched_job);

	panfrost_job_put(job);
}