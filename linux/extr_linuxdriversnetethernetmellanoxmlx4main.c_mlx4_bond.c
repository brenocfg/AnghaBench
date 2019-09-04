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
struct mlx4_priv {int /*<<< orphan*/  bond_mutex; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*) ; 
 int mlx4_do_bond (struct mlx4_dev*,int) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx4_is_bonded (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_master (struct mlx4_dev*) ; 
 int mlx4_mf_bond (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx4_bond(struct mlx4_dev *dev)
{
	int ret = 0;
	struct mlx4_priv *priv = mlx4_priv(dev);

	mutex_lock(&priv->bond_mutex);

	if (!mlx4_is_bonded(dev)) {
		ret = mlx4_do_bond(dev, true);
		if (ret)
			mlx4_err(dev, "Failed to bond device: %d\n", ret);
		if (!ret && mlx4_is_master(dev)) {
			ret = mlx4_mf_bond(dev);
			if (ret) {
				mlx4_err(dev, "bond for multifunction failed\n");
				mlx4_do_bond(dev, false);
			}
		}
	}

	mutex_unlock(&priv->bond_mutex);
	if (!ret)
		mlx4_dbg(dev, "Device is bonded\n");

	return ret;
}