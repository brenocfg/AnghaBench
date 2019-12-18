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
struct sxgbe_priv_data {unsigned int dma_tx_size; unsigned int dma_rx_size; TYPE_4__** txq; TYPE_3__* hw; int /*<<< orphan*/  mode; int /*<<< orphan*/  use_riwt; TYPE_1__** rxq; } ;
struct TYPE_8__ {int /*<<< orphan*/ * dma_tx; } ;
struct TYPE_7__ {TYPE_2__* desc; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* init_tx_desc ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* init_rx_desc ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * dma_rx; } ;

/* Variables and functions */
 int SXGBE_RX_QUEUES ; 
 int SXGBE_TX_QUEUES ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sxgbe_clear_descriptors(struct sxgbe_priv_data *priv)
{
	int i, j;
	unsigned int txsize = priv->dma_tx_size;
	unsigned int rxsize = priv->dma_rx_size;

	/* Clear the Rx/Tx descriptors */
	for (j = 0; j < SXGBE_RX_QUEUES; j++) {
		for (i = 0; i < rxsize; i++)
			priv->hw->desc->init_rx_desc(&priv->rxq[j]->dma_rx[i],
						     priv->use_riwt, priv->mode,
						     (i == rxsize - 1));
	}

	for (j = 0; j < SXGBE_TX_QUEUES; j++) {
		for (i = 0; i < txsize; i++)
			priv->hw->desc->init_tx_desc(&priv->txq[j]->dma_tx[i]);
	}
}