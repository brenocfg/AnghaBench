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
typedef  int u32 ;
typedef  int u16 ;
struct netsec_priv {int dummy; } ;
struct netsec_desc_ring {TYPE_1__* desc; struct netsec_de* vaddr; } ;
struct netsec_desc {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; int /*<<< orphan*/  dma_addr; } ;
struct netsec_de {int attr; int /*<<< orphan*/  buf_len_info; int /*<<< orphan*/  data_buf_addr_lw; int /*<<< orphan*/  data_buf_addr_up; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; int /*<<< orphan*/  dma_addr; } ;

/* Variables and functions */
 int DESC_NUM ; 
 int DESC_SZ ; 
 int NETSEC_RX_PKT_FS_FIELD ; 
 int NETSEC_RX_PKT_LD_FIELD ; 
 int NETSEC_RX_PKT_LS_FIELD ; 
 int NETSEC_RX_PKT_OWN_FIELD ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netsec_set_rx_de(struct netsec_priv *priv,
			     struct netsec_desc_ring *dring, u16 idx,
			     const struct netsec_desc *desc)
{
	struct netsec_de *de = dring->vaddr + DESC_SZ * idx;
	u32 attr = (1 << NETSEC_RX_PKT_OWN_FIELD) |
		   (1 << NETSEC_RX_PKT_FS_FIELD) |
		   (1 << NETSEC_RX_PKT_LS_FIELD);

	if (idx == DESC_NUM - 1)
		attr |= (1 << NETSEC_RX_PKT_LD_FIELD);

	de->data_buf_addr_up = upper_32_bits(desc->dma_addr);
	de->data_buf_addr_lw = lower_32_bits(desc->dma_addr);
	de->buf_len_info = desc->len;
	de->attr = attr;
	dma_wmb();

	dring->desc[idx].dma_addr = desc->dma_addr;
	dring->desc[idx].addr = desc->addr;
	dring->desc[idx].len = desc->len;
}