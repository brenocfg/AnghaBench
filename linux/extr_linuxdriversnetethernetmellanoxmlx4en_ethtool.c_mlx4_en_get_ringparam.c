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
struct mlx4_en_priv {TYPE_2__*** tx_ring; TYPE_1__** rx_ring; scalar_t__ port_up; } ;
struct ethtool_ringparam {int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  rx_pending; int /*<<< orphan*/  tx_max_pending; int /*<<< orphan*/  rx_max_pending; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct TYPE_3__ {int /*<<< orphan*/  size; int /*<<< orphan*/  actual_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_EN_MAX_RX_SIZE ; 
 int /*<<< orphan*/  MLX4_EN_MAX_TX_SIZE ; 
 size_t TX ; 
 int /*<<< orphan*/  memset (struct ethtool_ringparam*,int /*<<< orphan*/ ,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void mlx4_en_get_ringparam(struct net_device *dev,
				  struct ethtool_ringparam *param)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);

	memset(param, 0, sizeof(*param));
	param->rx_max_pending = MLX4_EN_MAX_RX_SIZE;
	param->tx_max_pending = MLX4_EN_MAX_TX_SIZE;
	param->rx_pending = priv->port_up ?
		priv->rx_ring[0]->actual_size : priv->rx_ring[0]->size;
	param->tx_pending = priv->tx_ring[TX][0]->size;
}