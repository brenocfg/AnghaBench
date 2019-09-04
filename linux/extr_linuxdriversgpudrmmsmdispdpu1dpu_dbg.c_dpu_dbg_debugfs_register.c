#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; int /*<<< orphan*/  enable_mask; } ;
struct TYPE_8__ {TYPE_3__ cmn; scalar_t__ entries; } ;
struct TYPE_5__ {char* name; int /*<<< orphan*/  enable_mask; } ;
struct TYPE_6__ {TYPE_1__ cmn; scalar_t__ entries; } ;
struct dpu_dbg_base {TYPE_4__ dbgbus_vbif_rt; TYPE_2__ dbgbus_dpu; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  debug_name ;

/* Variables and functions */
 char* DBGBUS_NAME_DPU ; 
 char* DBGBUS_NAME_VBIF_RT ; 
 int /*<<< orphan*/  DEFAULT_DBGBUS_DPU ; 
 int /*<<< orphan*/  DEFAULT_DBGBUS_VBIFRT ; 
 int EINVAL ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 struct dpu_dbg_base dpu_dbg_base ; 
 int /*<<< orphan*/  dpu_dbg_dump_fops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int dpu_dbg_debugfs_register(struct dentry *debugfs_root)
{
	static struct dpu_dbg_base *dbg = &dpu_dbg_base;
	char debug_name[80] = "";

	if (!debugfs_root)
		return -EINVAL;

	debugfs_create_file("dump", 0600, debugfs_root, NULL,
			&dpu_dbg_dump_fops);

	if (dbg->dbgbus_dpu.entries) {
		dbg->dbgbus_dpu.cmn.name = DBGBUS_NAME_DPU;
		snprintf(debug_name, sizeof(debug_name), "%s_dbgbus",
				dbg->dbgbus_dpu.cmn.name);
		dbg->dbgbus_dpu.cmn.enable_mask = DEFAULT_DBGBUS_DPU;
		debugfs_create_u32(debug_name, 0600, debugfs_root,
				&dbg->dbgbus_dpu.cmn.enable_mask);
	}

	if (dbg->dbgbus_vbif_rt.entries) {
		dbg->dbgbus_vbif_rt.cmn.name = DBGBUS_NAME_VBIF_RT;
		snprintf(debug_name, sizeof(debug_name), "%s_dbgbus",
				dbg->dbgbus_vbif_rt.cmn.name);
		dbg->dbgbus_vbif_rt.cmn.enable_mask = DEFAULT_DBGBUS_VBIFRT;
		debugfs_create_u32(debug_name, 0600, debugfs_root,
				&dbg->dbgbus_vbif_rt.cmn.enable_mask);
	}

	return 0;
}