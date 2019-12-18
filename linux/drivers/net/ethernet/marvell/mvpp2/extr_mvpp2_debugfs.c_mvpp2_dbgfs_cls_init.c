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
struct mvpp2 {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MVPP22_CLS_C2_N_ENTRIES ; 
 int MVPP2_CLS_FLOWS_TBL_SIZE ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int mvpp2_dbgfs_c2_entry_init (struct dentry*,struct mvpp2*,int) ; 
 int mvpp2_dbgfs_flow_tbl_entry_init (struct dentry*,struct mvpp2*,int) ; 

__attribute__((used)) static int mvpp2_dbgfs_cls_init(struct dentry *parent, struct mvpp2 *priv)
{
	struct dentry *cls_dir, *c2_dir, *flow_tbl_dir;
	int i, ret;

	cls_dir = debugfs_create_dir("classifier", parent);
	if (!cls_dir)
		return -ENOMEM;

	c2_dir = debugfs_create_dir("c2", cls_dir);
	if (!c2_dir)
		return -ENOMEM;

	for (i = 0; i < MVPP22_CLS_C2_N_ENTRIES; i++) {
		ret = mvpp2_dbgfs_c2_entry_init(c2_dir, priv, i);
		if (ret)
			return ret;
	}

	flow_tbl_dir = debugfs_create_dir("flow_table", cls_dir);
	if (!flow_tbl_dir)
		return -ENOMEM;

	for (i = 0; i < MVPP2_CLS_FLOWS_TBL_SIZE; i++) {
		ret = mvpp2_dbgfs_flow_tbl_entry_init(flow_tbl_dir, priv, i);
		if (ret)
			return ret;
	}

	return 0;
}