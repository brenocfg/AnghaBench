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
typedef  scalar_t__ u8 ;
struct net_device {int dummy; } ;
struct mlx5e_cee_config {scalar_t__ pfc_enable; } ;
struct TYPE_2__ {struct mlx5e_cee_config cee_cfg; } ;
struct mlx5e_priv {TYPE_1__ dcbx; } ;

/* Variables and functions */
 scalar_t__ MLX5E_CEE_STATE_DOWN ; 
 scalar_t__ MLX5E_CEE_STATE_UP ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx5e_dcbnl_setpfcstate(struct net_device *netdev, u8 state)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct mlx5e_cee_config *cee_cfg = &priv->dcbx.cee_cfg;

	if ((state != MLX5E_CEE_STATE_UP) && (state != MLX5E_CEE_STATE_DOWN))
		return;

	cee_cfg->pfc_enable = state;
}