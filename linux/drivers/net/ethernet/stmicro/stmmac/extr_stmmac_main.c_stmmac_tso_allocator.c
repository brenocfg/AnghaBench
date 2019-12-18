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
typedef  size_t u32 ;
struct stmmac_tx_queue {size_t cur_tx; struct dma_desc* dma_tx; int /*<<< orphan*/ * tx_skbuff; } ;
struct TYPE_2__ {int addr64; } ;
struct stmmac_priv {TYPE_1__ dma_cap; struct stmmac_tx_queue* tx_queue; } ;
struct dma_desc {int /*<<< orphan*/  des0; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TX_SIZE ; 
 size_t STMMAC_GET_ENTRY (size_t,int /*<<< orphan*/ ) ; 
 int TSO_MAX_BUFF_SIZE ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  stmmac_prepare_tso_tx_desc (struct stmmac_priv*,struct dma_desc*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_set_desc_addr (struct stmmac_priv*,struct dma_desc*,scalar_t__) ; 

__attribute__((used)) static void stmmac_tso_allocator(struct stmmac_priv *priv, dma_addr_t des,
				 int total_len, bool last_segment, u32 queue)
{
	struct stmmac_tx_queue *tx_q = &priv->tx_queue[queue];
	struct dma_desc *desc;
	u32 buff_size;
	int tmp_len;

	tmp_len = total_len;

	while (tmp_len > 0) {
		dma_addr_t curr_addr;

		tx_q->cur_tx = STMMAC_GET_ENTRY(tx_q->cur_tx, DMA_TX_SIZE);
		WARN_ON(tx_q->tx_skbuff[tx_q->cur_tx]);
		desc = tx_q->dma_tx + tx_q->cur_tx;

		curr_addr = des + (total_len - tmp_len);
		if (priv->dma_cap.addr64 <= 32)
			desc->des0 = cpu_to_le32(curr_addr);
		else
			stmmac_set_desc_addr(priv, desc, curr_addr);

		buff_size = tmp_len >= TSO_MAX_BUFF_SIZE ?
			    TSO_MAX_BUFF_SIZE : tmp_len;

		stmmac_prepare_tso_tx_desc(priv, desc, 0, buff_size,
				0, 1,
				(last_segment) && (tmp_len <= TSO_MAX_BUFF_SIZE),
				0, 0);

		tmp_len -= TSO_MAX_BUFF_SIZE;
	}
}