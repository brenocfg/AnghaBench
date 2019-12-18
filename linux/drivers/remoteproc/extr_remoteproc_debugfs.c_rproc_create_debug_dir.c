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
struct device {int dummy; } ;
struct rproc {int /*<<< orphan*/  dbg_dir; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct rproc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  rproc_carveouts_ops ; 
 int /*<<< orphan*/  rproc_crash_ops ; 
 int /*<<< orphan*/  rproc_dbg ; 
 int /*<<< orphan*/  rproc_name_ops ; 
 int /*<<< orphan*/  rproc_recovery_ops ; 
 int /*<<< orphan*/  rproc_rsc_table_ops ; 

void rproc_create_debug_dir(struct rproc *rproc)
{
	struct device *dev = &rproc->dev;

	if (!rproc_dbg)
		return;

	rproc->dbg_dir = debugfs_create_dir(dev_name(dev), rproc_dbg);
	if (!rproc->dbg_dir)
		return;

	debugfs_create_file("name", 0400, rproc->dbg_dir,
			    rproc, &rproc_name_ops);
	debugfs_create_file("recovery", 0400, rproc->dbg_dir,
			    rproc, &rproc_recovery_ops);
	debugfs_create_file("crash", 0200, rproc->dbg_dir,
			    rproc, &rproc_crash_ops);
	debugfs_create_file("resource_table", 0400, rproc->dbg_dir,
			    rproc, &rproc_rsc_table_ops);
	debugfs_create_file("carveout_memories", 0400, rproc->dbg_dir,
			    rproc, &rproc_carveouts_ops);
}