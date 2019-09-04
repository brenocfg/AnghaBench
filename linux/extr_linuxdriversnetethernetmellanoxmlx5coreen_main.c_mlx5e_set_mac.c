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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct mlx5e_priv {int /*<<< orphan*/  set_rx_mode_work; int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_lock_bh (struct net_device*) ; 
 int /*<<< orphan*/  netif_addr_unlock_bh (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5e_set_mac(struct net_device *netdev, void *addr)
{
	struct mlx5e_priv *priv = netdev_priv(netdev);
	struct sockaddr *saddr = addr;

	if (!is_valid_ether_addr(saddr->sa_data))
		return -EADDRNOTAVAIL;

	netif_addr_lock_bh(netdev);
	ether_addr_copy(netdev->dev_addr, saddr->sa_data);
	netif_addr_unlock_bh(netdev);

	queue_work(priv->wq, &priv->set_rx_mode_work);

	return 0;
}