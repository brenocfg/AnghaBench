#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int status; } ;
union ixgbe_adv_tx_desc {TYPE_1__ wb; } ;
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct xdp_umem {int dummy; } ;
struct ixgbe_tx_buffer {int /*<<< orphan*/ * xdpf; scalar_t__ gso_segs; scalar_t__ bytecount; } ;
struct TYPE_5__ {unsigned int bytes; unsigned int packets; } ;
struct ixgbe_ring {size_t next_to_clean; size_t next_to_use; size_t count; struct xdp_umem* xsk_umem; int /*<<< orphan*/  syncp; TYPE_2__ stats; struct ixgbe_tx_buffer* tx_buffer_info; } ;
struct TYPE_6__ {unsigned int total_bytes; unsigned int total_packets; int /*<<< orphan*/  work_limit; } ;
struct ixgbe_q_vector {TYPE_3__ tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_TXD_STAT_DD ; 
 union ixgbe_adv_tx_desc* IXGBE_TX_DESC (struct ixgbe_ring*,size_t) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_clean_xdp_tx_buffer (struct ixgbe_ring*,struct ixgbe_tx_buffer*) ; 
 int ixgbe_xmit_zc (struct ixgbe_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (union ixgbe_adv_tx_desc*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xsk_set_tx_need_wakeup (struct xdp_umem*) ; 
 int /*<<< orphan*/  xsk_umem_complete_tx (struct xdp_umem*,scalar_t__) ; 
 scalar_t__ xsk_umem_uses_need_wakeup (struct xdp_umem*) ; 

bool ixgbe_clean_xdp_tx_irq(struct ixgbe_q_vector *q_vector,
			    struct ixgbe_ring *tx_ring, int napi_budget)
{
	u16 ntc = tx_ring->next_to_clean, ntu = tx_ring->next_to_use;
	unsigned int total_packets = 0, total_bytes = 0;
	struct xdp_umem *umem = tx_ring->xsk_umem;
	union ixgbe_adv_tx_desc *tx_desc;
	struct ixgbe_tx_buffer *tx_bi;
	u32 xsk_frames = 0;

	tx_bi = &tx_ring->tx_buffer_info[ntc];
	tx_desc = IXGBE_TX_DESC(tx_ring, ntc);

	while (ntc != ntu) {
		if (!(tx_desc->wb.status & cpu_to_le32(IXGBE_TXD_STAT_DD)))
			break;

		total_bytes += tx_bi->bytecount;
		total_packets += tx_bi->gso_segs;

		if (tx_bi->xdpf)
			ixgbe_clean_xdp_tx_buffer(tx_ring, tx_bi);
		else
			xsk_frames++;

		tx_bi->xdpf = NULL;

		tx_bi++;
		tx_desc++;
		ntc++;
		if (unlikely(ntc == tx_ring->count)) {
			ntc = 0;
			tx_bi = tx_ring->tx_buffer_info;
			tx_desc = IXGBE_TX_DESC(tx_ring, 0);
		}

		/* issue prefetch for next Tx descriptor */
		prefetch(tx_desc);
	}

	tx_ring->next_to_clean = ntc;

	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->stats.bytes += total_bytes;
	tx_ring->stats.packets += total_packets;
	u64_stats_update_end(&tx_ring->syncp);
	q_vector->tx.total_bytes += total_bytes;
	q_vector->tx.total_packets += total_packets;

	if (xsk_frames)
		xsk_umem_complete_tx(umem, xsk_frames);

	if (xsk_umem_uses_need_wakeup(tx_ring->xsk_umem))
		xsk_set_tx_need_wakeup(tx_ring->xsk_umem);

	return ixgbe_xmit_zc(tx_ring, q_vector->tx.work_limit);
}