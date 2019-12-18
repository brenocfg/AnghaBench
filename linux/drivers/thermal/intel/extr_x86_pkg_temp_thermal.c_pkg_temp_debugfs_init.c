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
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  debugfs ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkg_interrupt_cnt ; 
 int /*<<< orphan*/  pkg_work_cnt ; 

__attribute__((used)) static void pkg_temp_debugfs_init(void)
{
	debugfs = debugfs_create_dir("pkg_temp_thermal", NULL);

	debugfs_create_u32("pkg_thres_interrupt", S_IRUGO, debugfs,
			   &pkg_interrupt_cnt);
	debugfs_create_u32("pkg_thres_work", S_IRUGO, debugfs,
			   &pkg_work_cnt);
}