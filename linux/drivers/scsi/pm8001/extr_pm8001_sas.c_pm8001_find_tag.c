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
typedef  int /*<<< orphan*/  u32 ;
struct sas_task {struct pm8001_ccb_info* lldd_task; } ;
struct pm8001_ccb_info {int /*<<< orphan*/  ccb_tag; } ;

/* Variables and functions */

__attribute__((used)) static int pm8001_find_tag(struct sas_task *task, u32 *tag)
{
	if (task->lldd_task) {
		struct pm8001_ccb_info *ccb;
		ccb = task->lldd_task;
		*tag = ccb->ccb_tag;
		return 1;
	}
	return 0;
}