#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int qpn; } ;
struct TYPE_12__ {void* usr_page; } ;
struct TYPE_11__ {int /*<<< orphan*/  mtt; } ;
struct TYPE_10__ {TYPE_2__* uar; } ;
struct mlx4_en_tx_ring {int sp_cqn; int cons; int last_nr_txbb; int size; int buf_size; int /*<<< orphan*/  queue_index; int /*<<< orphan*/  sp_affinity_mask; int /*<<< orphan*/  sp_qp_state; TYPE_6__ sp_qp; TYPE_5__ sp_context; TYPE_4__ sp_wqres; TYPE_3__ bf; scalar_t__ bf_alloced; int /*<<< orphan*/  qpn; int /*<<< orphan*/  sp_stride; void* mr_key; void* doorbell_qpn; int /*<<< orphan*/  free_tx_desc; int /*<<< orphan*/  buf; int /*<<< orphan*/  tx_info; scalar_t__ prod; } ;
struct mlx4_en_tx_info {int dummy; } ;
struct mlx4_en_priv {int /*<<< orphan*/  dev; struct mlx4_en_dev* mdev; } ;
struct TYPE_8__ {int key; } ;
struct mlx4_en_dev {int /*<<< orphan*/  dev; TYPE_1__ mr; } ;
struct TYPE_9__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_QP_STATE_RST ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_en_fill_qp_context (struct mlx4_en_priv*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,TYPE_5__*) ; 
 int /*<<< orphan*/  mlx4_en_free_tx_desc ; 
 int mlx4_qp_to_ready (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ *) ; 
 int mlx4_to_hw_uar_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_set_xps_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int mlx4_en_activate_tx_ring(struct mlx4_en_priv *priv,
			     struct mlx4_en_tx_ring *ring,
			     int cq, int user_prio)
{
	struct mlx4_en_dev *mdev = priv->mdev;
	int err;

	ring->sp_cqn = cq;
	ring->prod = 0;
	ring->cons = 0xffffffff;
	ring->last_nr_txbb = 1;
	memset(ring->tx_info, 0, ring->size * sizeof(struct mlx4_en_tx_info));
	memset(ring->buf, 0, ring->buf_size);
	ring->free_tx_desc = mlx4_en_free_tx_desc;

	ring->sp_qp_state = MLX4_QP_STATE_RST;
	ring->doorbell_qpn = cpu_to_be32(ring->sp_qp.qpn << 8);
	ring->mr_key = cpu_to_be32(mdev->mr.key);

	mlx4_en_fill_qp_context(priv, ring->size, ring->sp_stride, 1, 0, ring->qpn,
				ring->sp_cqn, user_prio, &ring->sp_context);
	if (ring->bf_alloced)
		ring->sp_context.usr_page =
			cpu_to_be32(mlx4_to_hw_uar_index(mdev->dev,
							 ring->bf.uar->index));

	err = mlx4_qp_to_ready(mdev->dev, &ring->sp_wqres.mtt, &ring->sp_context,
			       &ring->sp_qp, &ring->sp_qp_state);
	if (!cpumask_empty(&ring->sp_affinity_mask))
		netif_set_xps_queue(priv->dev, &ring->sp_affinity_mask,
				    ring->queue_index);

	return err;
}