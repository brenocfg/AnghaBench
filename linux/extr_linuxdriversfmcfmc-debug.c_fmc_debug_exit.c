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
struct fmc_device {scalar_t__ dbg_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (scalar_t__) ; 

void fmc_debug_exit(struct fmc_device *fmc)
{
	if (fmc->dbg_dir)
		debugfs_remove_recursive(fmc->dbg_dir);
}