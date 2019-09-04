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
 int /*<<< orphan*/ * debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vas_debugfs ; 

void vas_init_dbgdir(void)
{
	static bool first_time = true;

	if (!first_time)
		return;

	first_time = false;
	vas_debugfs = debugfs_create_dir("vas", NULL);
	if (IS_ERR(vas_debugfs))
		vas_debugfs = NULL;
}