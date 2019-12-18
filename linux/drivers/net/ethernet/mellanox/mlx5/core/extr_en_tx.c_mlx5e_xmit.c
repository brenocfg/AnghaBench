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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5e_txqsq {int dummy; } ;
struct mlx5e_tx_wqe {int dummy; } ;
struct mlx5e_priv {struct mlx5e_txqsq** txq2sq; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 struct sk_buff* mlx5e_accel_handle_tx (struct sk_buff*,struct mlx5e_txqsq*,struct net_device*,struct mlx5e_tx_wqe**,int /*<<< orphan*/ *) ; 
 struct mlx5e_tx_wqe* mlx5e_sq_fetch_wqe (struct mlx5e_txqsq*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_sq_xmit (struct mlx5e_txqsq*,struct sk_buff*,struct mlx5e_tx_wqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

netdev_tx_t mlx5e_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5e_tx_wqe *wqe;
	struct mlx5e_txqsq *sq;
	u16 pi;

	sq = priv->txq2sq[skb_get_queue_mapping(skb)];
	wqe = mlx5e_sq_fetch_wqe(sq, sizeof(*wqe), &pi);

	/* might send skbs and update wqe and pi */
	skb = mlx5e_accel_handle_tx(skb, sq, dev, &wqe, &pi);
	if (unlikely(!skb))
		return NETDEV_TX_OK;

	return mlx5e_sq_xmit(sq, skb, wqe, pi, netdev_xmit_more());
}