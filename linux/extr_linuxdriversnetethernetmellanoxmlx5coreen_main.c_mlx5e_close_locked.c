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
struct mlx5e_priv {int /*<<< orphan*/  channels; int /*<<< orphan*/  netdev; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_STATE_OPENED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_close_channels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_deactivate_priv_channels (struct mlx5e_priv*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int mlx5e_close_locked(struct net_device *netdev)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);

	/* May already be CLOSED in case a previous configuration operation
	 * (e.g RX/TX queue size change) that involves close&open failed.
	 */
	if (!test_bit(MLX5E_STATE_OPENED, &priv->state))
		return 0;

	clear_bit(MLX5E_STATE_OPENED, &priv->state);

	netif_carrier_off(priv->netdev);
	mlx5e_deactivate_priv_channels(priv);
	mlx5e_close_channels(&priv->channels);

	return 0;
}