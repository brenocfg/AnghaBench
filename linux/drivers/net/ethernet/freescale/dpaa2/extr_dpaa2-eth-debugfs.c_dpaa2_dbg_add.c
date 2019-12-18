#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct dentry* dir; } ;
struct dpaa2_eth_priv {TYPE_2__ dbg; TYPE_1__* net_dev; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct dpaa2_eth_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpaa2_dbg_ch_ops ; 
 int /*<<< orphan*/  dpaa2_dbg_cpu_ops ; 
 int /*<<< orphan*/  dpaa2_dbg_fq_ops ; 
 int /*<<< orphan*/  dpaa2_dbg_root ; 

void dpaa2_dbg_add(struct dpaa2_eth_priv *priv)
{
	struct dentry *dir;

	/* Create a directory for the interface */
	dir = debugfs_create_dir(priv->net_dev->name, dpaa2_dbg_root);
	priv->dbg.dir = dir;

	/* per-cpu stats file */
	debugfs_create_file("cpu_stats", 0444, dir, priv, &dpaa2_dbg_cpu_ops);

	/* per-fq stats file */
	debugfs_create_file("fq_stats", 0444, dir, priv, &dpaa2_dbg_fq_ops);

	/* per-fq stats file */
	debugfs_create_file("ch_stats", 0444, dir, priv, &dpaa2_dbg_ch_ops);
}