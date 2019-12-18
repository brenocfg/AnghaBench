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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct mlx5i_priv {int /*<<< orphan*/  qkey; } ;
struct mlx5e_txqsq {int dummy; } ;
struct mlx5e_priv {struct mlx5i_priv* ppriv; struct mlx5e_txqsq** txq2sq; } ;
struct mlx5_ib_ah {int /*<<< orphan*/  av; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 struct mlx5e_priv* mlx5i_epriv (struct net_device*) ; 
 int mlx5i_sq_xmit (struct mlx5e_txqsq*,struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_xmit_more () ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 struct mlx5_ib_ah* to_mah (struct ib_ah*) ; 

__attribute__((used)) static int mlx5i_xmit(struct net_device *dev, struct sk_buff *skb,
		      struct ib_ah *address, u32 dqpn)
{
	struct mlx5e_priv *epriv = mlx5i_epriv(dev);
	struct mlx5e_txqsq *sq   = epriv->txq2sq[skb_get_queue_mapping(skb)];
	struct mlx5_ib_ah *mah   = to_mah(address);
	struct mlx5i_priv *ipriv = epriv->ppriv;

	return mlx5i_sq_xmit(sq, skb, &mah->av, dqpn, ipriv->qkey, netdev_xmit_more());
}