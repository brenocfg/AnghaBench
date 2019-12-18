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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct mlx5e_txqsq {int pc; int sqn; int /*<<< orphan*/  uar_map; int /*<<< orphan*/  txq; TYPE_1__* stats; int /*<<< orphan*/  stop_room; int /*<<< orphan*/  cc; struct mlx5_wq_cyc wq; } ;
struct mlx5e_tx_wqe_info {int num_dma; int num_wqebbs; struct sk_buff* skb; int /*<<< orphan*/  num_bytes; } ;
struct mlx5_wqe_ctrl_seg {void* qpn_ds; void* opmod_idx_opcode; } ;
struct TYPE_4__ {int tx_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  stopped; } ;

/* Variables and functions */
 int SKBTX_HW_TSTAMP ; 
 int SKBTX_IN_PROGRESS ; 
 int __netdev_tx_sent_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  mlx5e_notify_hw (struct mlx5_wq_cyc*,int,int /*<<< orphan*/ ,struct mlx5_wqe_ctrl_seg*) ; 
 int /*<<< orphan*/  mlx5e_wqc_has_room_for (struct mlx5_wq_cyc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (int /*<<< orphan*/ ) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline void
mlx5e_txwqe_complete(struct mlx5e_txqsq *sq, struct sk_buff *skb,
		     u8 opcode, u16 ds_cnt, u8 num_wqebbs, u32 num_bytes, u8 num_dma,
		     struct mlx5e_tx_wqe_info *wi, struct mlx5_wqe_ctrl_seg *cseg,
		     bool xmit_more)
{
	struct mlx5_wq_cyc *wq = &sq->wq;
	bool send_doorbell;

	wi->num_bytes = num_bytes;
	wi->num_dma = num_dma;
	wi->num_wqebbs = num_wqebbs;
	wi->skb = skb;

	cseg->opmod_idx_opcode = cpu_to_be32((sq->pc << 8) | opcode);
	cseg->qpn_ds           = cpu_to_be32((sq->sqn << 8) | ds_cnt);

	if (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP))
		skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;

	sq->pc += wi->num_wqebbs;
	if (unlikely(!mlx5e_wqc_has_room_for(wq, sq->cc, sq->pc, sq->stop_room))) {
		netif_tx_stop_queue(sq->txq);
		sq->stats->stopped++;
	}

	send_doorbell = __netdev_tx_sent_queue(sq->txq, num_bytes,
					       xmit_more);
	if (send_doorbell)
		mlx5e_notify_hw(wq, sq->pc, sq->uar_map, cseg);
}