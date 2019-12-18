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
 int /*<<< orphan*/ * intel_th_dbg ; 

void intel_th_debug_init(void)
{
	intel_th_dbg = debugfs_create_dir("intel_th", NULL);
	if (IS_ERR(intel_th_dbg))
		intel_th_dbg = NULL;
}