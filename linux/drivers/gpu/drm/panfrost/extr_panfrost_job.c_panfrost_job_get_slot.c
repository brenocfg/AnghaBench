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
struct panfrost_job {int requirements; TYPE_2__* pfdev; } ;
struct TYPE_3__ {int nr_core_groups; } ;
struct TYPE_4__ {TYPE_1__ features; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_ISSUE_8987 ; 
 int PANFROST_JD_REQ_CORE_GRP_MASK ; 
 int PANFROST_JD_REQ_FS ; 
 int PANFROST_JD_REQ_ONLY_COMPUTE ; 
 scalar_t__ panfrost_has_hw_issue (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int panfrost_job_get_slot(struct panfrost_job *job)
{
	/* JS0: fragment jobs.
	 * JS1: vertex/tiler jobs
	 * JS2: compute jobs
	 */
	if (job->requirements & PANFROST_JD_REQ_FS)
		return 0;

/* Not exposed to userspace yet */
#if 0
	if (job->requirements & PANFROST_JD_REQ_ONLY_COMPUTE) {
		if ((job->requirements & PANFROST_JD_REQ_CORE_GRP_MASK) &&
		    (job->pfdev->features.nr_core_groups == 2))
			return 2;
		if (panfrost_has_hw_issue(job->pfdev, HW_ISSUE_8987))
			return 2;
	}
#endif
	return 1;
}