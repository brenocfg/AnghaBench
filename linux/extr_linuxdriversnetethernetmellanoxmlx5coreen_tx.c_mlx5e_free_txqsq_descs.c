#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {struct mlx5e_tx_wqe_info* wqe_info; } ;
struct mlx5e_txqsq {scalar_t__ cc; scalar_t__ pc; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dma_fifo_cc; TYPE_1__ db; int /*<<< orphan*/  wq; } ;
struct mlx5e_tx_wqe_info {int num_dma; scalar_t__ num_wqebbs; struct sk_buff* skb; } ;
struct mlx5e_sq_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 size_t mlx5_wq_cyc_ctr2ix (int /*<<< orphan*/ *,scalar_t__) ; 
 struct mlx5e_sq_dma* mlx5e_dma_get (struct mlx5e_txqsq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_tx_dma_unmap (int /*<<< orphan*/ ,struct mlx5e_sq_dma*) ; 

void mlx5e_free_txqsq_descs(struct mlx5e_txqsq *sq)
{
	struct mlx5e_tx_wqe_info *wi;
	struct sk_buff *skb;
	u16 ci;
	int i;

	while (sq->cc != sq->pc) {
		ci = mlx5_wq_cyc_ctr2ix(&sq->wq, sq->cc);
		wi = &sq->db.wqe_info[ci];
		skb = wi->skb;

		if (!skb) { /* nop */
			sq->cc++;
			continue;
		}

		for (i = 0; i < wi->num_dma; i++) {
			struct mlx5e_sq_dma *dma =
				mlx5e_dma_get(sq, sq->dma_fifo_cc++);

			mlx5e_tx_dma_unmap(sq->pdev, dma);
		}

		dev_kfree_skb_any(skb);
		sq->cc += wi->num_wqebbs;
	}
}