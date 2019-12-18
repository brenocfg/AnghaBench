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
struct netsec_tx_pkt_ctrl {int cksum_offload_flag; int tcp_seg_offload_flag; int tcp_seg_len; } ;
struct netsec_priv {int dummy; } ;
struct netsec_desc_ring {int head; struct netsec_desc* desc; struct netsec_de* vaddr; } ;
struct netsec_desc {int len; scalar_t__ buf_type; void* xdpf; void* skb; int /*<<< orphan*/  dma_addr; } ;
struct netsec_de {int buf_len_info; int attr; int /*<<< orphan*/  data_buf_addr_lw; int /*<<< orphan*/  data_buf_addr_up; } ;

/* Variables and functions */
 int DESC_NUM ; 
 int DESC_SZ ; 
 int NETSEC_RING_GMAC ; 
 int NETSEC_TX_LAST ; 
 int NETSEC_TX_SHIFT_CO ; 
 int NETSEC_TX_SHIFT_FS_FIELD ; 
 int NETSEC_TX_SHIFT_LD_FIELD ; 
 int NETSEC_TX_SHIFT_OWN_FIELD ; 
 int NETSEC_TX_SHIFT_PT_FIELD ; 
 int NETSEC_TX_SHIFT_SO ; 
 int NETSEC_TX_SHIFT_TDRID_FIELD ; 
 int NETSEC_TX_SHIFT_TRS_FIELD ; 
 scalar_t__ TYPE_NETSEC_SKB ; 
 scalar_t__ TYPE_NETSEC_XDP_NDO ; 
 scalar_t__ TYPE_NETSEC_XDP_TX ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netsec_set_tx_de(struct netsec_priv *priv,
			     struct netsec_desc_ring *dring,
			     const struct netsec_tx_pkt_ctrl *tx_ctrl,
			     const struct netsec_desc *desc, void *buf)
{
	int idx = dring->head;
	struct netsec_de *de;
	u32 attr;

	de = dring->vaddr + (DESC_SZ * idx);

	attr = (1 << NETSEC_TX_SHIFT_OWN_FIELD) |
	       (1 << NETSEC_TX_SHIFT_PT_FIELD) |
	       (NETSEC_RING_GMAC << NETSEC_TX_SHIFT_TDRID_FIELD) |
	       (1 << NETSEC_TX_SHIFT_FS_FIELD) |
	       (1 << NETSEC_TX_LAST) |
	       (tx_ctrl->cksum_offload_flag << NETSEC_TX_SHIFT_CO) |
	       (tx_ctrl->tcp_seg_offload_flag << NETSEC_TX_SHIFT_SO) |
	       (1 << NETSEC_TX_SHIFT_TRS_FIELD);
	if (idx == DESC_NUM - 1)
		attr |= (1 << NETSEC_TX_SHIFT_LD_FIELD);

	de->data_buf_addr_up = upper_32_bits(desc->dma_addr);
	de->data_buf_addr_lw = lower_32_bits(desc->dma_addr);
	de->buf_len_info = (tx_ctrl->tcp_seg_len << 16) | desc->len;
	de->attr = attr;

	dring->desc[idx] = *desc;
	if (desc->buf_type == TYPE_NETSEC_SKB)
		dring->desc[idx].skb = buf;
	else if (desc->buf_type == TYPE_NETSEC_XDP_TX ||
		 desc->buf_type == TYPE_NETSEC_XDP_NDO)
		dring->desc[idx].xdpf = buf;

	/* move head ahead */
	dring->head = (dring->head + 1) % DESC_NUM;
}