#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_7__ {void* threshold; } ;
struct TYPE_6__ {int rx_fifo_size; int tx_fifo_size; } ;
struct stmmac_priv {int /*<<< orphan*/  ioaddr; TYPE_5__* plat; int /*<<< orphan*/  dma_buf_sz; TYPE_2__ xstats; TYPE_1__ dma_cap; } ;
struct TYPE_10__ {int rx_queues_to_use; int tx_queues_to_use; int rx_fifo_size; int tx_fifo_size; TYPE_4__* tx_queues_cfg; TYPE_3__* rx_queues_cfg; scalar_t__ tx_coe; scalar_t__ force_sf_dma_mode; scalar_t__ force_thresh_dma_mode; } ;
struct TYPE_9__ {int /*<<< orphan*/  mode_to_use; } ;
struct TYPE_8__ {int /*<<< orphan*/  mode_to_use; } ;

/* Variables and functions */
 void* SF_DMA_MODE ; 
 int /*<<< orphan*/  stmmac_dma_rx_mode (struct stmmac_priv*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_dma_tx_mode (struct stmmac_priv*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_set_dma_bfsize (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int tc ; 

__attribute__((used)) static void stmmac_dma_operation_mode(struct stmmac_priv *priv)
{
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	int rxfifosz = priv->plat->rx_fifo_size;
	int txfifosz = priv->plat->tx_fifo_size;
	u32 txmode = 0;
	u32 rxmode = 0;
	u32 chan = 0;
	u8 qmode = 0;

	if (rxfifosz == 0)
		rxfifosz = priv->dma_cap.rx_fifo_size;
	if (txfifosz == 0)
		txfifosz = priv->dma_cap.tx_fifo_size;

	/* Adjust for real per queue fifo size */
	rxfifosz /= rx_channels_count;
	txfifosz /= tx_channels_count;

	if (priv->plat->force_thresh_dma_mode) {
		txmode = tc;
		rxmode = tc;
	} else if (priv->plat->force_sf_dma_mode || priv->plat->tx_coe) {
		/*
		 * In case of GMAC, SF mode can be enabled
		 * to perform the TX COE in HW. This depends on:
		 * 1) TX COE if actually supported
		 * 2) There is no bugged Jumbo frame support
		 *    that needs to not insert csum in the TDES.
		 */
		txmode = SF_DMA_MODE;
		rxmode = SF_DMA_MODE;
		priv->xstats.threshold = SF_DMA_MODE;
	} else {
		txmode = tc;
		rxmode = SF_DMA_MODE;
	}

	/* configure all channels */
	for (chan = 0; chan < rx_channels_count; chan++) {
		qmode = priv->plat->rx_queues_cfg[chan].mode_to_use;

		stmmac_dma_rx_mode(priv, priv->ioaddr, rxmode, chan,
				rxfifosz, qmode);
		stmmac_set_dma_bfsize(priv, priv->ioaddr, priv->dma_buf_sz,
				chan);
	}

	for (chan = 0; chan < tx_channels_count; chan++) {
		qmode = priv->plat->tx_queues_cfg[chan].mode_to_use;

		stmmac_dma_tx_mode(priv, priv->ioaddr, txmode, chan,
				txfifosz, qmode);
	}
}