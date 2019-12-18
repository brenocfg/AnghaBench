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
struct hfi1_ibdev {int /*<<< orphan*/ * hfi1_ibdev_dbg; int /*<<< orphan*/  hfi1_ibdev_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfi1_dbg_root ; 
 int /*<<< orphan*/  hfi1_fault_exit_debugfs (struct hfi1_ibdev*) ; 

void hfi1_dbg_ibdev_exit(struct hfi1_ibdev *ibd)
{
	if (!hfi1_dbg_root)
		goto out;
	hfi1_fault_exit_debugfs(ibd);
	debugfs_remove(ibd->hfi1_ibdev_link);
	debugfs_remove_recursive(ibd->hfi1_ibdev_dbg);
out:
	ibd->hfi1_ibdev_dbg = NULL;
}