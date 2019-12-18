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
typedef  int /*<<< orphan*/  u8 ;
struct pm8001_tmf_task {int /*<<< orphan*/  tmf; } ;
struct domain_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TMF_ABORT_TASK_SET ; 
 int pm8001_issue_ssp_tmf (struct domain_device*,int /*<<< orphan*/ *,struct pm8001_tmf_task*) ; 

int pm8001_abort_task_set(struct domain_device *dev, u8 *lun)
{
	struct pm8001_tmf_task tmf_task;

	tmf_task.tmf = TMF_ABORT_TASK_SET;
	return pm8001_issue_ssp_tmf(dev, lun, &tmf_task);
}