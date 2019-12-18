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
 int WQ_CPU_INTENSIVE ; 
 int WQ_HIGHPRI ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  comp_vector_wq ; 

int rvt_driver_cq_init(void)
{
	comp_vector_wq = alloc_workqueue("%s", WQ_HIGHPRI | WQ_CPU_INTENSIVE,
					 0, "rdmavt_cq");
	if (!comp_vector_wq)
		return -ENOMEM;

	return 0;
}