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
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  siw_cm_wq ; 

int siw_cm_init(void)
{
	/*
	 * create_single_workqueue for strict ordering
	 */
	siw_cm_wq = create_singlethread_workqueue("siw_cm_wq");
	if (!siw_cm_wq)
		return -ENOMEM;

	return 0;
}