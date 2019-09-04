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
 int /*<<< orphan*/ * crcs ; 
 int /*<<< orphan*/  s3c_pm_run_sysram (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s3c_pm_runcheck ; 

void s3c_pm_check_restore(void)
{
	if (crcs != NULL)
		s3c_pm_run_sysram(s3c_pm_runcheck, crcs);
}