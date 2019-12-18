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
typedef  int /*<<< orphan*/  u16 ;
struct xdp_umem {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_params {int dummy; } ;
struct TYPE_2__ {struct mlx5e_params params; } ;
struct mlx5e_priv {TYPE_1__ channels; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX5E_RQ_GROUP_XSK ; 
 int /*<<< orphan*/  mlx5e_qid_get_ch_if_in_group (struct mlx5e_params*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx5e_xsk_disable_umem (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 
 int mlx5e_xsk_enable_umem (struct mlx5e_priv*,struct xdp_umem*,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

int mlx5e_xsk_setup_umem(struct net_device *dev, struct xdp_umem *umem, u16 qid)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5e_params *params = &priv->channels.params;
	u16 ix;

	if (unlikely(!mlx5e_qid_get_ch_if_in_group(params, qid, MLX5E_RQ_GROUP_XSK, &ix)))
		return -EINVAL;

	return umem ? mlx5e_xsk_enable_umem(priv, umem, ix) :
		      mlx5e_xsk_disable_umem(priv, ix);
}