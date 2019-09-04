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
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qpn; } ;
struct mlx5i_priv {TYPE_1__ qp; } ;
struct mlx5e_priv {struct mlx5i_priv* ppriv; } ;

/* Variables and functions */
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 int /*<<< orphan*/  mlx5i_pkey_del_qpn (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5i_uninit_underlay_qp (struct mlx5e_priv*) ; 

void mlx5i_dev_cleanup(struct net_device *dev)
{
	struct mlx5e_priv    *priv   = mlx5i_epriv(dev);
	struct mlx5i_priv    *ipriv = priv->ppriv;

	mlx5i_uninit_underlay_qp(priv);

	/* Delete QPN to net-device mapping from HT */
	mlx5i_pkey_del_qpn(dev, ipriv->qp.qpn);
}