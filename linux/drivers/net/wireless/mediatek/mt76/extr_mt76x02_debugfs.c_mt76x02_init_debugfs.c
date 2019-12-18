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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  temp; } ;
struct mt76x02_dev {int /*<<< orphan*/  tx_hang_reset; TYPE_2__ mt76; int /*<<< orphan*/  enable_tpc; TYPE_1__ cal; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_bool (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_devm_seqfile (int /*<<< orphan*/ ,char*,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct mt76x02_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u32 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_u8 (char*,int,struct dentry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_ampdu_stat ; 
 int /*<<< orphan*/  fops_dfs_stat ; 
 int /*<<< orphan*/  fops_edcca ; 
 struct dentry* mt76_register_debugfs (TYPE_2__*) ; 
 int /*<<< orphan*/  read_agc ; 
 int /*<<< orphan*/  read_txpower ; 

void mt76x02_init_debugfs(struct mt76x02_dev *dev)
{
	struct dentry *dir;

	dir = mt76_register_debugfs(&dev->mt76);
	if (!dir)
		return;

	debugfs_create_u8("temperature", 0400, dir, &dev->cal.temp);
	debugfs_create_bool("tpc", 0600, dir, &dev->enable_tpc);

	debugfs_create_file("edcca", 0600, dir, dev, &fops_edcca);
	debugfs_create_file("ampdu_stat", 0400, dir, dev, &fops_ampdu_stat);
	debugfs_create_file("dfs_stats", 0400, dir, dev, &fops_dfs_stat);
	debugfs_create_devm_seqfile(dev->mt76.dev, "txpower", dir,
				    read_txpower);

	debugfs_create_devm_seqfile(dev->mt76.dev, "agc", dir, read_agc);

	debugfs_create_u32("tx_hang_reset", 0400, dir, &dev->tx_hang_reset);
}