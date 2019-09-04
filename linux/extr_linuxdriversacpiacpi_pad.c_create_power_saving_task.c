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
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kthread_run (int /*<<< orphan*/ ,void*,char*,size_t) ; 
 int /*<<< orphan*/  power_saving_thread ; 
 size_t ps_tsk_num ; 
 int /*<<< orphan*/ ** ps_tsks ; 

__attribute__((used)) static int create_power_saving_task(void)
{
	int rc;

	ps_tsks[ps_tsk_num] = kthread_run(power_saving_thread,
		(void *)(unsigned long)ps_tsk_num,
		"acpi_pad/%d", ps_tsk_num);

	if (IS_ERR(ps_tsks[ps_tsk_num])) {
		rc = PTR_ERR(ps_tsks[ps_tsk_num]);
		ps_tsks[ps_tsk_num] = NULL;
	} else {
		rc = 0;
		ps_tsk_num++;
	}

	return rc;
}