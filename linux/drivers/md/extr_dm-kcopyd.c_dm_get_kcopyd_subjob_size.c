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
 int /*<<< orphan*/  DEFAULT_SUB_JOB_SIZE_KB ; 
 int /*<<< orphan*/  MAX_SUB_JOB_SIZE_KB ; 
 unsigned int __dm_get_module_param (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcopyd_subjob_size_kb ; 

__attribute__((used)) static unsigned dm_get_kcopyd_subjob_size(void)
{
	unsigned sub_job_size_kb;

	sub_job_size_kb = __dm_get_module_param(&kcopyd_subjob_size_kb,
						DEFAULT_SUB_JOB_SIZE_KB,
						MAX_SUB_JOB_SIZE_KB);

	return sub_job_size_kb << 1;
}