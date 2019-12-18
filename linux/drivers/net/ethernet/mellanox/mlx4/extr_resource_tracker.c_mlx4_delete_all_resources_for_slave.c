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
struct TYPE_5__ {TYPE_4__* slave_list; } ;
struct TYPE_6__ {TYPE_1__ res_tracker; } ;
struct TYPE_7__ {TYPE_2__ master; } ;
struct mlx4_priv {TYPE_3__ mfunc; } ;
struct mlx4_dev {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_reset_roce_gids (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rem_slave_counters (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  rem_slave_cqs (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  rem_slave_eqs (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  rem_slave_fs_rule (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  rem_slave_macs (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  rem_slave_mrs (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  rem_slave_mtts (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  rem_slave_qps (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  rem_slave_srqs (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  rem_slave_vlans (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  rem_slave_xrcdns (struct mlx4_dev*,int) ; 

void mlx4_delete_all_resources_for_slave(struct mlx4_dev *dev, int slave)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	mlx4_reset_roce_gids(dev, slave);
	mutex_lock(&priv->mfunc.master.res_tracker.slave_list[slave].mutex);
	rem_slave_vlans(dev, slave);
	rem_slave_macs(dev, slave);
	rem_slave_fs_rule(dev, slave);
	rem_slave_qps(dev, slave);
	rem_slave_srqs(dev, slave);
	rem_slave_cqs(dev, slave);
	rem_slave_mrs(dev, slave);
	rem_slave_eqs(dev, slave);
	rem_slave_mtts(dev, slave);
	rem_slave_counters(dev, slave);
	rem_slave_xrcdns(dev, slave);
	mutex_unlock(&priv->mfunc.master.res_tracker.slave_list[slave].mutex);
}