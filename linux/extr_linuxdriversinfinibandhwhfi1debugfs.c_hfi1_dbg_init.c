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
 int /*<<< orphan*/  DEBUGFS_SEQ_FILE_CREATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_stats ; 
 int /*<<< orphan*/  driver_stats_names ; 
 int /*<<< orphan*/  hfi1_dbg_root ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void hfi1_dbg_init(void)
{
	hfi1_dbg_root  = debugfs_create_dir(DRIVER_NAME, NULL);
	if (!hfi1_dbg_root)
		pr_warn("init of debugfs failed\n");
	DEBUGFS_SEQ_FILE_CREATE(driver_stats_names, hfi1_dbg_root, NULL);
	DEBUGFS_SEQ_FILE_CREATE(driver_stats, hfi1_dbg_root, NULL);
}