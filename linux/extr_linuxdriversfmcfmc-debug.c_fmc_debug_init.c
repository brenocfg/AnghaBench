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
struct fmc_device {int /*<<< orphan*/  dbg_sdb_dump; int /*<<< orphan*/  dbg_dir; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMC_DBG_SDB_DUMP ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct fmc_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmc_dbgfs_sdb_dump ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

int fmc_debug_init(struct fmc_device *fmc)
{
	fmc->dbg_dir = debugfs_create_dir(dev_name(&fmc->dev), NULL);
	if (IS_ERR_OR_NULL(fmc->dbg_dir)) {
		pr_err("FMC: Cannot create debugfs\n");
		return PTR_ERR(fmc->dbg_dir);
	}

	fmc->dbg_sdb_dump = debugfs_create_file(FMC_DBG_SDB_DUMP, 0444,
						fmc->dbg_dir, fmc,
						&fmc_dbgfs_sdb_dump);
	if (IS_ERR_OR_NULL(fmc->dbg_sdb_dump))
		pr_err("FMC: Cannot create debugfs file %s\n",
		       FMC_DBG_SDB_DUMP);

	return 0;
}