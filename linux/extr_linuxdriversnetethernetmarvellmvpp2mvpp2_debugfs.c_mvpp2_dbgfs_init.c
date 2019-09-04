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
struct mvpp2 {int port_count; int /*<<< orphan*/ * port_list; struct dentry* dbgfs_dir; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 char const* MVPP2_DRIVER_NAME ; 
 struct dentry* debugfs_create_dir (char const*,struct dentry*) ; 
 struct dentry* debugfs_lookup (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_dbgfs_cleanup (struct mvpp2*) ; 
 int mvpp2_dbgfs_flow_init (struct dentry*,struct mvpp2*) ; 
 int mvpp2_dbgfs_port_init (struct dentry*,int /*<<< orphan*/ ) ; 
 int mvpp2_dbgfs_prs_init (struct dentry*,struct mvpp2*) ; 

void mvpp2_dbgfs_init(struct mvpp2 *priv, const char *name)
{
	struct dentry *mvpp2_dir, *mvpp2_root;
	int ret, i;

	mvpp2_root = debugfs_lookup(MVPP2_DRIVER_NAME, NULL);
	if (!mvpp2_root) {
		mvpp2_root = debugfs_create_dir(MVPP2_DRIVER_NAME, NULL);
		if (IS_ERR(mvpp2_root))
			return;
	}

	mvpp2_dir = debugfs_create_dir(name, mvpp2_root);
	if (IS_ERR(mvpp2_dir))
		return;

	priv->dbgfs_dir = mvpp2_dir;

	ret = mvpp2_dbgfs_prs_init(mvpp2_dir, priv);
	if (ret)
		goto err;

	for (i = 0; i < priv->port_count; i++) {
		ret = mvpp2_dbgfs_port_init(mvpp2_dir, priv->port_list[i]);
		if (ret)
			goto err;
	}

	ret = mvpp2_dbgfs_flow_init(mvpp2_dir, priv);
	if (ret)
		goto err;

	return;
err:
	mvpp2_dbgfs_cleanup(priv);
}