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
 int MVPP2_N_PRS_FLOWS ; 
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int mvpp2_dbgfs_flow_entry_init (struct dentry*,struct mvpp2*,int) ; 

__attribute__((used)) static int mvpp2_dbgfs_flow_init(struct dentry *parent, struct mvpp2 *priv)
{
	struct dentry *flow_dir;
	int i, ret;

	flow_dir = debugfs_create_dir("flows", parent);

	for (i = 0; i < MVPP2_N_PRS_FLOWS; i++) {
		ret = mvpp2_dbgfs_flow_entry_init(flow_dir, priv, i);
		if (ret)
			return ret;
	}

	return 0;
}