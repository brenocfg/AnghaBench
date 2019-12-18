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
struct mvpp2_dbgfs_flow_entry {int flow; struct mvpp2* priv; } ;
struct mvpp2 {int port_count; int /*<<< orphan*/ * port_list; TYPE_1__* dbgfs_entries; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct mvpp2_dbgfs_flow_entry* flow_entries; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct mvpp2_dbgfs_flow_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_dbgfs_flow_dec_hits_fops ; 
 int /*<<< orphan*/  mvpp2_dbgfs_flow_id_fops ; 
 int mvpp2_dbgfs_flow_port_init (struct dentry*,int /*<<< orphan*/ ,struct mvpp2_dbgfs_flow_entry*) ; 
 int /*<<< orphan*/  mvpp2_dbgfs_flow_type_fops ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int mvpp2_dbgfs_flow_entry_init(struct dentry *parent,
				       struct mvpp2 *priv, int flow)
{
	struct mvpp2_dbgfs_flow_entry *entry;
	struct dentry *flow_entry_dir;
	char flow_entry_name[10];
	int i, ret;

	sprintf(flow_entry_name, "%02d", flow);

	flow_entry_dir = debugfs_create_dir(flow_entry_name, parent);

	entry = &priv->dbgfs_entries->flow_entries[flow];

	entry->flow = flow;
	entry->priv = priv;

	debugfs_create_file("dec_hits", 0444, flow_entry_dir, entry,
			    &mvpp2_dbgfs_flow_dec_hits_fops);

	debugfs_create_file("type", 0444, flow_entry_dir, entry,
			    &mvpp2_dbgfs_flow_type_fops);

	debugfs_create_file("id", 0444, flow_entry_dir, entry,
			    &mvpp2_dbgfs_flow_id_fops);

	/* Create entry for each port */
	for (i = 0; i < priv->port_count; i++) {
		ret = mvpp2_dbgfs_flow_port_init(flow_entry_dir,
						 priv->port_list[i], entry);
		if (ret)
			return ret;
	}

	return 0;
}