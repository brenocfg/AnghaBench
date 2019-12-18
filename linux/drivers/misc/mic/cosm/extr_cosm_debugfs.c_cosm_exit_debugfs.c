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
 int /*<<< orphan*/  cosm_dbg ; 
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 

void cosm_exit_debugfs(void)
{
	debugfs_remove(cosm_dbg);
}