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
struct mvpp2_dbgfs_c2_entry {int id; struct mvpp2* priv; } ;
struct mvpp2 {TYPE_1__* dbgfs_entries; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct mvpp2_dbgfs_c2_entry* c2_entries; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int MVPP22_CLS_C2_N_ENTRIES ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct mvpp2_dbgfs_c2_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_dbgfs_flow_c2_enable_fops ; 
 int /*<<< orphan*/  mvpp2_dbgfs_flow_c2_hits_fops ; 
 int /*<<< orphan*/  mvpp2_dbgfs_flow_c2_rxq_fops ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int mvpp2_dbgfs_c2_entry_init(struct dentry *parent,
				     struct mvpp2 *priv, int id)
{
	struct mvpp2_dbgfs_c2_entry *entry;
	struct dentry *c2_entry_dir;
	char c2_entry_name[10];

	if (id >= MVPP22_CLS_C2_N_ENTRIES)
		return -EINVAL;

	sprintf(c2_entry_name, "%03d", id);

	c2_entry_dir = debugfs_create_dir(c2_entry_name, parent);
	if (!c2_entry_dir)
		return -ENOMEM;

	entry = &priv->dbgfs_entries->c2_entries[id];

	entry->id = id;
	entry->priv = priv;

	debugfs_create_file("hits", 0444, c2_entry_dir, entry,
			    &mvpp2_dbgfs_flow_c2_hits_fops);

	debugfs_create_file("default_rxq", 0444, c2_entry_dir, entry,
			    &mvpp2_dbgfs_flow_c2_rxq_fops);

	debugfs_create_file("rss_enable", 0444, c2_entry_dir, entry,
			    &mvpp2_dbgfs_flow_c2_enable_fops);

	return 0;
}