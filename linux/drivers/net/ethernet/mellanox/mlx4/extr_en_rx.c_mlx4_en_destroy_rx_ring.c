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
typedef  int u32 ;
typedef  int u16 ;
struct mlx4_en_rx_ring {int /*<<< orphan*/ * rx_info; int /*<<< orphan*/  wqres; int /*<<< orphan*/  xdp_rxq; int /*<<< orphan*/  xdp_prog; } ;
struct mlx4_en_priv {struct mlx4_en_dev* mdev; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  state_lock; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 scalar_t__ TXBB_SIZE ; 
 int /*<<< orphan*/  bpf_prog_put (struct bpf_prog*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_en_rx_ring*) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_hwq_res (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct bpf_prog* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

void mlx4_en_destroy_rx_ring(struct mlx4_en_priv *priv,
			     struct mlx4_en_rx_ring **pring,
			     u32 size, u16 stride)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	struct mlx4_en_rx_ring *ring = *pring;
	struct bpf_prog *old_prog;

	old_prog = rcu_dereference_protected(
					ring->xdp_prog,
					lockdep_is_held(&mdev->state_lock));
	if (old_prog)
		bpf_prog_put(old_prog);
	xdp_rxq_info_unreg(&ring->xdp_rxq);
	mlx4_free_hwq_res(mdev->dev, &ring->wqres, size * stride + TXBB_SIZE);
	kvfree(ring->rx_info);
	ring->rx_info = NULL;
	kfree(ring);
	*pring = NULL;
}