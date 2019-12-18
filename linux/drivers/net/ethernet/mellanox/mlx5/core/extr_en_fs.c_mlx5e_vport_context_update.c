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
struct mlx5e_l2_table {int /*<<< orphan*/  promisc_enabled; int /*<<< orphan*/  allmulti_enabled; } ;
struct TYPE_2__ {struct mlx5e_l2_table l2; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; TYPE_1__ fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_NVPRT_LIST_TYPE_MC ; 
 int /*<<< orphan*/  MLX5_NVPRT_LIST_TYPE_UC ; 
 int /*<<< orphan*/  mlx5_modify_nic_vport_promisc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_vport_context_update_addr_list (struct mlx5e_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_vport_context_update(struct mlx5e_priv *priv)
{
	struct mlx5e_l2_table *ea = &priv->fs.l2;

	mlx5e_vport_context_update_addr_list(priv, MLX5_NVPRT_LIST_TYPE_UC);
	mlx5e_vport_context_update_addr_list(priv, MLX5_NVPRT_LIST_TYPE_MC);
	mlx5_modify_nic_vport_promisc(priv->mdev, 0,
				      ea->allmulti_enabled,
				      ea->promisc_enabled);
}