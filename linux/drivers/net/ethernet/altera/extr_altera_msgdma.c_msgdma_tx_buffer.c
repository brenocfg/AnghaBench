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
struct tse_buffer {int /*<<< orphan*/  len; int /*<<< orphan*/  dma_addr; } ;
struct altera_tse_private {int /*<<< orphan*/  tx_dma_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGDMA_DESC_CTL_TX_SINGLE ; 
 int /*<<< orphan*/  MSGDMA_DESC_TX_STRIDE ; 
 int /*<<< orphan*/  burst_seq_num ; 
 int /*<<< orphan*/  control ; 
 int /*<<< orphan*/  csrwr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgdma_descroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_addr_hi ; 
 int /*<<< orphan*/  read_addr_lo ; 
 int /*<<< orphan*/  stride ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_addr_hi ; 
 int /*<<< orphan*/  write_addr_lo ; 

int msgdma_tx_buffer(struct altera_tse_private *priv, struct tse_buffer *buffer)
{
	csrwr32(lower_32_bits(buffer->dma_addr), priv->tx_dma_desc,
		msgdma_descroffs(read_addr_lo));
	csrwr32(upper_32_bits(buffer->dma_addr), priv->tx_dma_desc,
		msgdma_descroffs(read_addr_hi));
	csrwr32(0, priv->tx_dma_desc, msgdma_descroffs(write_addr_lo));
	csrwr32(0, priv->tx_dma_desc, msgdma_descroffs(write_addr_hi));
	csrwr32(buffer->len, priv->tx_dma_desc, msgdma_descroffs(len));
	csrwr32(0, priv->tx_dma_desc, msgdma_descroffs(burst_seq_num));
	csrwr32(MSGDMA_DESC_TX_STRIDE, priv->tx_dma_desc,
		msgdma_descroffs(stride));
	csrwr32(MSGDMA_DESC_CTL_TX_SINGLE, priv->tx_dma_desc,
		msgdma_descroffs(control));
	return 0;
}