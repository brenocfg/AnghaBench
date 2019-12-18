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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mlx4_en_priv {TYPE_1__** rx_ring; int /*<<< orphan*/ * tx_ring_num; struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  state_lock; } ;
struct bpf_prog {TYPE_2__* aux; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  xdp_prog; } ;

/* Variables and functions */
 size_t TX_XDP ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 struct bpf_prog* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mlx4_xdp_query(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_en_dev *mdev = priv->mdev;
	const struct bpf_prog *xdp_prog;
	u32 prog_id = 0;

	if (!priv->tx_ring_num[TX_XDP])
		return prog_id;

	mutex_lock(&mdev->state_lock);
	xdp_prog = rcu_dereference_protected(
		priv->rx_ring[0]->xdp_prog,
		lockdep_is_held(&mdev->state_lock));
	if (xdp_prog)
		prog_id = xdp_prog->aux->id;
	mutex_unlock(&mdev->state_lock);

	return prog_id;
}