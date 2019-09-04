#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  debugfs_entry; } ;
struct bdisp_dev {TYPE_1__ dbg; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  dirname ;

/* Variables and functions */
 char* BDISP_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bdisp_dbg_create_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdisp_debugfs_remove (struct bdisp_dev*) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  last_nodes ; 
 int /*<<< orphan*/  last_nodes_raw ; 
 int /*<<< orphan*/  last_request ; 
 int /*<<< orphan*/  perf ; 
 int /*<<< orphan*/  regs ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 

int bdisp_debugfs_create(struct bdisp_dev *bdisp)
{
	char dirname[16];

	snprintf(dirname, sizeof(dirname), "%s%d", BDISP_NAME, bdisp->id);
	bdisp->dbg.debugfs_entry = debugfs_create_dir(dirname, NULL);
	if (!bdisp->dbg.debugfs_entry)
		goto err;

	if (!bdisp_dbg_create_entry(regs))
		goto err;

	if (!bdisp_dbg_create_entry(last_nodes))
		goto err;

	if (!bdisp_dbg_create_entry(last_nodes_raw))
		goto err;

	if (!bdisp_dbg_create_entry(last_request))
		goto err;

	if (!bdisp_dbg_create_entry(perf))
		goto err;

	return 0;

err:
	bdisp_debugfs_remove(bdisp);
	return -ENOMEM;
}