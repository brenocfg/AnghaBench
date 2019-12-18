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
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  _driver_stats_file_ops ; 
 int /*<<< orphan*/  _driver_stats_names_file_ops ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_dbg_root ; 

void hfi1_dbg_init(void)
{
	hfi1_dbg_root  = debugfs_create_dir(DRIVER_NAME, NULL);
	debugfs_create_file("driver_stats_names", 0444, hfi1_dbg_root, NULL,
			    &_driver_stats_names_file_ops);
	debugfs_create_file("driver_stats", 0444, hfi1_dbg_root, NULL,
			    &_driver_stats_file_ops);
}