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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HFI1_MAX_ACTIVE_WORKQUEUE_ENTRIES ; 
 int WQ_CPU_INTENSIVE ; 
 int WQ_HIGHPRI ; 
 int WQ_MEM_RECLAIM ; 
 int WQ_SYSFS ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opfn_wq ; 

int opfn_init(void)
{
	opfn_wq = alloc_workqueue("hfi_opfn",
				  WQ_SYSFS | WQ_HIGHPRI | WQ_CPU_INTENSIVE |
				  WQ_MEM_RECLAIM,
				  HFI1_MAX_ACTIVE_WORKQUEUE_ENTRIES);
	if (!opfn_wq)
		return -ENOMEM;

	return 0;
}