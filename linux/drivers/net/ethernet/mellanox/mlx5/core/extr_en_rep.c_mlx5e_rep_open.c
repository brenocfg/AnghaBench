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
struct net_device {int dummy; } ;
struct mlx5e_rep_priv {struct mlx5_eswitch_rep* rep; } ;
struct mlx5e_priv {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  mdev; struct mlx5e_rep_priv* ppriv; } ;
struct mlx5_eswitch_rep {int /*<<< orphan*/  vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_VPORT_ADMIN_STATE_UP ; 
 int /*<<< orphan*/  MLX5_VPORT_STATE_OP_MOD_ESW_VPORT ; 
 int /*<<< orphan*/  mlx5_modify_vport_admin_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mlx5e_open_locked (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 

__attribute__((used)) static int mlx5e_rep_open(struct net_device *dev)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5e_rep_priv *rpriv = priv->ppriv;
	struct mlx5_eswitch_rep *rep = rpriv->rep;
	int err;

	mutex_lock(&priv->state_lock);
	err = mlx5e_open_locked(dev);
	if (err)
		goto unlock;

	if (!mlx5_modify_vport_admin_state(priv->mdev,
					   MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
					   rep->vport, 1,
					   MLX5_VPORT_ADMIN_STATE_UP))
		netif_carrier_on(dev);

unlock:
	mutex_unlock(&priv->state_lock);
	return err;
}