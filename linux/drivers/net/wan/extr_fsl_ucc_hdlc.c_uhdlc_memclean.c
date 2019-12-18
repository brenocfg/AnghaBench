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
struct ucc_hdlc_private {scalar_t__ dma_tx_addr; int /*<<< orphan*/ * tx_buffer; int /*<<< orphan*/  dev; scalar_t__ dma_rx_addr; int /*<<< orphan*/ * rx_buffer; int /*<<< orphan*/ * uccf; int /*<<< orphan*/ * uf_regs; int /*<<< orphan*/ * tx_skbuff; int /*<<< orphan*/ * rx_skbuff; scalar_t__ ucc_pram_offset; TYPE_1__* ucc_pram; scalar_t__ dma_tx_bd; int /*<<< orphan*/ * tx_bd_base; scalar_t__ dma_rx_bd; int /*<<< orphan*/ * rx_bd_base; } ;
struct qe_bd {int dummy; } ;
struct TYPE_2__ {scalar_t__ tiptr; scalar_t__ riptr; } ;

/* Variables and functions */
 int MAX_RX_BUF_LENGTH ; 
 int RX_BD_RING_LEN ; 
 int TX_BD_RING_LEN ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qe_muram_free (scalar_t__) ; 
 int /*<<< orphan*/  ucc_fast_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uhdlc_memclean(struct ucc_hdlc_private *priv)
{
	qe_muram_free(priv->ucc_pram->riptr);
	qe_muram_free(priv->ucc_pram->tiptr);

	if (priv->rx_bd_base) {
		dma_free_coherent(priv->dev,
				  RX_BD_RING_LEN * sizeof(struct qe_bd),
				  priv->rx_bd_base, priv->dma_rx_bd);

		priv->rx_bd_base = NULL;
		priv->dma_rx_bd = 0;
	}

	if (priv->tx_bd_base) {
		dma_free_coherent(priv->dev,
				  TX_BD_RING_LEN * sizeof(struct qe_bd),
				  priv->tx_bd_base, priv->dma_tx_bd);

		priv->tx_bd_base = NULL;
		priv->dma_tx_bd = 0;
	}

	if (priv->ucc_pram) {
		qe_muram_free(priv->ucc_pram_offset);
		priv->ucc_pram = NULL;
		priv->ucc_pram_offset = 0;
	 }

	kfree(priv->rx_skbuff);
	priv->rx_skbuff = NULL;

	kfree(priv->tx_skbuff);
	priv->tx_skbuff = NULL;

	if (priv->uf_regs) {
		iounmap(priv->uf_regs);
		priv->uf_regs = NULL;
	}

	if (priv->uccf) {
		ucc_fast_free(priv->uccf);
		priv->uccf = NULL;
	}

	if (priv->rx_buffer) {
		dma_free_coherent(priv->dev,
				  RX_BD_RING_LEN * MAX_RX_BUF_LENGTH,
				  priv->rx_buffer, priv->dma_rx_addr);
		priv->rx_buffer = NULL;
		priv->dma_rx_addr = 0;
	}

	if (priv->tx_buffer) {
		dma_free_coherent(priv->dev,
				  TX_BD_RING_LEN * MAX_RX_BUF_LENGTH,
				  priv->tx_buffer, priv->dma_tx_addr);
		priv->tx_buffer = NULL;
		priv->dma_tx_addr = 0;
	}
}