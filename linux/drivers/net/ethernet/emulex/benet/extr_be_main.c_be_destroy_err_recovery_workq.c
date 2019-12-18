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
 int /*<<< orphan*/ * be_err_recovery_workq ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void be_destroy_err_recovery_workq(void)
{
	if (!be_err_recovery_workq)
		return;

	flush_workqueue(be_err_recovery_workq);
	destroy_workqueue(be_err_recovery_workq);
	be_err_recovery_workq = NULL;
}