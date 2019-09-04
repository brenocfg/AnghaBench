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
struct mlx5e_priv {int /*<<< orphan*/  set_rx_mode_work; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5e_set_rx_mode(struct net_device *dev)
{
	struct mlx5e_priv *priv = netdev_priv(dev);

	queue_work(priv->wq, &priv->set_rx_mode_work);
}