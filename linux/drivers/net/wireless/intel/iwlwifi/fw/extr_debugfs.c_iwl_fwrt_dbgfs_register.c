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
struct TYPE_2__ {int /*<<< orphan*/  wk; } ;
struct iwl_fw_runtime {TYPE_1__ timestamp; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FWRT_DEBUGFS_ADD_FILE (int /*<<< orphan*/ ,struct dentry*,int) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwl_fw_timestamp_marker_wk ; 
 int /*<<< orphan*/  send_hcmd ; 
 int /*<<< orphan*/  timestamp_marker ; 

void iwl_fwrt_dbgfs_register(struct iwl_fw_runtime *fwrt,
			    struct dentry *dbgfs_dir)
{
	INIT_DELAYED_WORK(&fwrt->timestamp.wk, iwl_fw_timestamp_marker_wk);
	FWRT_DEBUGFS_ADD_FILE(timestamp_marker, dbgfs_dir, 0200);
	FWRT_DEBUGFS_ADD_FILE(send_hcmd, dbgfs_dir, 0200);
}