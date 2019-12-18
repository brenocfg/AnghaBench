#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  buf_len; int /*<<< orphan*/  lstatus; } ;
union enetc_rx_bd {TYPE_3__ r; } ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ len; } ;
struct napi_struct {int dummy; } ;
struct TYPE_8__ {int packets; int bytes; } ;
struct enetc_bdr {int next_to_clean; int bd_count; TYPE_4__ stats; TYPE_2__* ndev; int /*<<< orphan*/  index; int /*<<< orphan*/  idr; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_6__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 union enetc_rx_bd* ENETC_RXBD (struct enetc_bdr,int) ; 
 int ENETC_RXBD_BUNDLE ; 
 int /*<<< orphan*/  ENETC_RXBD_ERR_MASK ; 
 int ENETC_RXBD_LSTATUS (int /*<<< orphan*/ ) ; 
 int ENETC_RXBD_LSTATUS_F ; 
 int /*<<< orphan*/  ENETC_RXB_DMA_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  enetc_add_rx_buff_to_skb (struct enetc_bdr*,int,int /*<<< orphan*/ ,struct sk_buff*) ; 
 int enetc_bd_unused (struct enetc_bdr*) ; 
 int /*<<< orphan*/  enetc_get_offloads (struct enetc_bdr*,union enetc_rx_bd*,struct sk_buff*) ; 
 struct sk_buff* enetc_map_rx_buff_to_skb (struct enetc_bdr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enetc_process_skb (struct enetc_bdr*,struct sk_buff*) ; 
 int enetc_refill_rx_ring (struct enetc_bdr*,int) ; 
 int /*<<< orphan*/  enetc_wr_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  napi_gro_receive (struct napi_struct*,struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int enetc_clean_rx_ring(struct enetc_bdr *rx_ring,
			       struct napi_struct *napi, int work_limit)
{
	int rx_frm_cnt = 0, rx_byte_cnt = 0;
	int cleaned_cnt, i;

	cleaned_cnt = enetc_bd_unused(rx_ring);
	/* next descriptor to process */
	i = rx_ring->next_to_clean;

	while (likely(rx_frm_cnt < work_limit)) {
		union enetc_rx_bd *rxbd;
		struct sk_buff *skb;
		u32 bd_status;
		u16 size;

		if (cleaned_cnt >= ENETC_RXBD_BUNDLE) {
			int count = enetc_refill_rx_ring(rx_ring, cleaned_cnt);

			cleaned_cnt -= count;
		}

		rxbd = ENETC_RXBD(*rx_ring, i);
		bd_status = le32_to_cpu(rxbd->r.lstatus);
		if (!bd_status)
			break;

		enetc_wr_reg(rx_ring->idr, BIT(rx_ring->index));
		dma_rmb(); /* for reading other rxbd fields */
		size = le16_to_cpu(rxbd->r.buf_len);
		skb = enetc_map_rx_buff_to_skb(rx_ring, i, size);
		if (!skb)
			break;

		enetc_get_offloads(rx_ring, rxbd, skb);

		cleaned_cnt++;
		rxbd++;
		i++;
		if (unlikely(i == rx_ring->bd_count)) {
			i = 0;
			rxbd = ENETC_RXBD(*rx_ring, 0);
		}

		if (unlikely(bd_status &
			     ENETC_RXBD_LSTATUS(ENETC_RXBD_ERR_MASK))) {
			dev_kfree_skb(skb);
			while (!(bd_status & ENETC_RXBD_LSTATUS_F)) {
				dma_rmb();
				bd_status = le32_to_cpu(rxbd->r.lstatus);
				rxbd++;
				i++;
				if (unlikely(i == rx_ring->bd_count)) {
					i = 0;
					rxbd = ENETC_RXBD(*rx_ring, 0);
				}
			}

			rx_ring->ndev->stats.rx_dropped++;
			rx_ring->ndev->stats.rx_errors++;

			break;
		}

		/* not last BD in frame? */
		while (!(bd_status & ENETC_RXBD_LSTATUS_F)) {
			bd_status = le32_to_cpu(rxbd->r.lstatus);
			size = ENETC_RXB_DMA_SIZE;

			if (bd_status & ENETC_RXBD_LSTATUS_F) {
				dma_rmb();
				size = le16_to_cpu(rxbd->r.buf_len);
			}

			enetc_add_rx_buff_to_skb(rx_ring, i, size, skb);

			cleaned_cnt++;
			rxbd++;
			i++;
			if (unlikely(i == rx_ring->bd_count)) {
				i = 0;
				rxbd = ENETC_RXBD(*rx_ring, 0);
			}
		}

		rx_byte_cnt += skb->len;

		enetc_process_skb(rx_ring, skb);

		napi_gro_receive(napi, skb);

		rx_frm_cnt++;
	}

	rx_ring->next_to_clean = i;

	rx_ring->stats.packets += rx_frm_cnt;
	rx_ring->stats.bytes += rx_byte_cnt;

	return rx_frm_cnt;
}