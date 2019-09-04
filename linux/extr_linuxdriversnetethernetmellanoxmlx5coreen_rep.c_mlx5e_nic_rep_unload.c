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
struct mlx5e_rep_priv {int /*<<< orphan*/  tc_ht; int /*<<< orphan*/  netdev; } ;
struct mlx5e_priv {int /*<<< orphan*/  state; } ;
struct mlx5_eswitch_rep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  mlx5e_remove_sqs_fwd_rules (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_rep_neigh_cleanup (struct mlx5e_rep_priv*) ; 
 struct mlx5e_rep_priv* mlx5e_rep_to_rep_priv (struct mlx5_eswitch_rep*) ; 
 int /*<<< orphan*/  mlx5e_tc_esw_cleanup (int /*<<< orphan*/ *) ; 
 struct mlx5e_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_nic_rep_unload(struct mlx5_eswitch_rep *rep)
{
	struct mlx5e_rep_priv *rpriv = mlx5e_rep_to_rep_priv(rep);
	struct mlx5e_priv *priv = netdev_priv(rpriv->netdev);

	if (test_bit(MLX5E_STATE_OPENED, &priv->state))
		mlx5e_remove_sqs_fwd_rules(priv);

	/* clean uplink offloaded TC rules, delete shared tc flow table */
	mlx5e_tc_esw_cleanup(&rpriv->tc_ht);

	mlx5e_rep_neigh_cleanup(rpriv);
}