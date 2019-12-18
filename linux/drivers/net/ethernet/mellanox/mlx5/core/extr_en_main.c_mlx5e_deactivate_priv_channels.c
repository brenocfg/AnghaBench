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
struct mlx5e_priv {int /*<<< orphan*/  channels; int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5e_deactivate_channels (int /*<<< orphan*/ *) ; 
 scalar_t__ mlx5e_is_vport_rep (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_redirect_rqts_to_drop (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_remove_sqs_fwd_rules (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_xdp_tx_disable (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_xsk_redirect_rqts_to_drop (struct mlx5e_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (int /*<<< orphan*/ ) ; 

void mlx5e_deactivate_priv_channels(struct mlx5e_priv *priv)
{
	mlx5e_xsk_redirect_rqts_to_drop(priv, &priv->channels);

	mlx5e_redirect_rqts_to_drop(priv);

	if (mlx5e_is_vport_rep(priv))
		mlx5e_remove_sqs_fwd_rules(priv);

	/* FIXME: This is a W/A only for tx timeout watch dog false alarm when
	 * polling for inactive tx queues.
	 */
	netif_tx_stop_all_queues(priv->netdev);
	netif_tx_disable(priv->netdev);
	mlx5e_xdp_tx_disable(priv);
	mlx5e_deactivate_channels(&priv->channels);
}