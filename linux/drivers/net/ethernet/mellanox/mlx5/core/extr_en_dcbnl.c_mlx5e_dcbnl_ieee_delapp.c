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
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dscp_app_cnt; } ;
struct TYPE_3__ {scalar_t__* dscp2prio; } ;
struct mlx5e_priv {TYPE_2__ dcbx; TYPE_1__ dcbx_dp; int /*<<< orphan*/  mdev; } ;
struct dcb_app {scalar_t__ selector; size_t protocol; scalar_t__ priority; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int EOPNOTSUPP ; 
 scalar_t__ IEEE_8021QAZ_APP_SEL_DSCP ; 
 size_t MLX5E_MAX_DSCP ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_DSCP_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_QPTS_TRUST_PCP ; 
 int dcb_ieee_delapp (struct net_device*,struct dcb_app*) ; 
 int mlx5e_set_dscp2prio (struct mlx5e_priv*,size_t,int /*<<< orphan*/ ) ; 
 int mlx5e_set_trust_state (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  vport_group_manager ; 

__attribute__((used)) static int mlx5e_dcbnl_ieee_delapp(struct net_device *dev, struct dcb_app *app)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	int err;

	if  (!MLX5_CAP_GEN(priv->mdev, vport_group_manager) ||
	     !MLX5_DSCP_SUPPORTED(priv->mdev))
		return -EOPNOTSUPP;

	if ((app->selector != IEEE_8021QAZ_APP_SEL_DSCP) ||
	    (app->protocol >= MLX5E_MAX_DSCP))
		return -EINVAL;

	/* Skip if no dscp app entry */
	if (!priv->dcbx.dscp_app_cnt)
		return -ENOENT;

	/* Check if the entry matches fw setting */
	if (app->priority != priv->dcbx_dp.dscp2prio[app->protocol])
		return -ENOENT;

	/* Delete the app entry */
	err = dcb_ieee_delapp(dev, app);
	if (err)
		return err;

	/* Reset the priority mapping back to zero */
	err = mlx5e_set_dscp2prio(priv, app->protocol, 0);
	if (err)
		goto fw_err;

	priv->dcbx.dscp_app_cnt--;

	/* Check if need to switch to pcp trust state */
	if (!priv->dcbx.dscp_app_cnt)
		err = mlx5e_set_trust_state(priv, MLX5_QPTS_TRUST_PCP);

	return err;

fw_err:
	mlx5e_set_trust_state(priv, MLX5_QPTS_TRUST_PCP);
	return err;
}