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
struct mvpp2_dbgfs_flow_tbl_entry {int id; struct mvpp2* priv; } ;
struct mvpp2 {TYPE_1__* dbgfs_entries; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct mvpp2_dbgfs_flow_tbl_entry* flt_entries; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MVPP2_CLS_FLOWS_TBL_SIZE ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct mvpp2_dbgfs_flow_tbl_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_dbgfs_flow_flt_hits_fops ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int mvpp2_dbgfs_flow_tbl_entry_init(struct dentry *parent,
					   struct mvpp2 *priv, int id)
{
	struct mvpp2_dbgfs_flow_tbl_entry *entry;
	struct dentry *flow_tbl_entry_dir;
	char flow_tbl_entry_name[10];

	if (id >= MVPP2_CLS_FLOWS_TBL_SIZE)
		return -EINVAL;

	sprintf(flow_tbl_entry_name, "%03d", id);

	flow_tbl_entry_dir = debugfs_create_dir(flow_tbl_entry_name, parent);
	if (!flow_tbl_entry_dir)
		return -ENOMEM;

	entry = &priv->dbgfs_entries->flt_entries[id];

	entry->id = id;
	entry->priv = priv;

	debugfs_create_file("hits", 0444, flow_tbl_entry_dir, entry,
			    &mvpp2_dbgfs_flow_flt_hits_fops);

	return 0;
}