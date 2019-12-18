#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct stmmac_tx_queue {int /*<<< orphan*/  tx_tail_addr; int /*<<< orphan*/  dma_tx_phy; } ;
struct stmmac_rx_queue {scalar_t__ rx_tail_addr; scalar_t__ dma_rx_phy; } ;
struct stmmac_priv {scalar_t__ mode; int /*<<< orphan*/  ioaddr; TYPE_1__* plat; struct stmmac_tx_queue* tx_queue; struct stmmac_rx_queue* rx_queue; int /*<<< orphan*/  device; scalar_t__ extend_desc; } ;
struct dma_desc {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  pbl; } ;
struct TYPE_6__ {size_t rx_queues_to_use; size_t tx_queues_to_use; TYPE_2__* dma_cfg; scalar_t__ axi; } ;

/* Variables and functions */
 int DMA_RX_SIZE ; 
 int EINVAL ; 
 scalar_t__ STMMAC_RING_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 size_t max (size_t,size_t) ; 
 int /*<<< orphan*/  stmmac_axi (struct stmmac_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stmmac_dma_init (struct stmmac_priv*,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  stmmac_init_chan (struct stmmac_priv*,int /*<<< orphan*/ ,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  stmmac_init_rx_chan (struct stmmac_priv*,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  stmmac_init_tx_chan (struct stmmac_priv*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 int stmmac_reset (struct stmmac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_set_rx_tail_ptr (struct stmmac_priv*,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  stmmac_set_tx_tail_ptr (struct stmmac_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int stmmac_init_dma_engine(struct stmmac_priv *priv)
{
	u32 rx_channels_count = priv->plat->rx_queues_to_use;
	u32 tx_channels_count = priv->plat->tx_queues_to_use;
	u32 dma_csr_ch = max(rx_channels_count, tx_channels_count);
	struct stmmac_rx_queue *rx_q;
	struct stmmac_tx_queue *tx_q;
	u32 chan = 0;
	int atds = 0;
	int ret = 0;

	if (!priv->plat->dma_cfg || !priv->plat->dma_cfg->pbl) {
		dev_err(priv->device, "Invalid DMA configuration\n");
		return -EINVAL;
	}

	if (priv->extend_desc && (priv->mode == STMMAC_RING_MODE))
		atds = 1;

	ret = stmmac_reset(priv, priv->ioaddr);
	if (ret) {
		dev_err(priv->device, "Failed to reset the dma\n");
		return ret;
	}

	/* DMA Configuration */
	stmmac_dma_init(priv, priv->ioaddr, priv->plat->dma_cfg, atds);

	if (priv->plat->axi)
		stmmac_axi(priv, priv->ioaddr, priv->plat->axi);

	/* DMA CSR Channel configuration */
	for (chan = 0; chan < dma_csr_ch; chan++)
		stmmac_init_chan(priv, priv->ioaddr, priv->plat->dma_cfg, chan);

	/* DMA RX Channel Configuration */
	for (chan = 0; chan < rx_channels_count; chan++) {
		rx_q = &priv->rx_queue[chan];

		stmmac_init_rx_chan(priv, priv->ioaddr, priv->plat->dma_cfg,
				    rx_q->dma_rx_phy, chan);

		rx_q->rx_tail_addr = rx_q->dma_rx_phy +
			    (DMA_RX_SIZE * sizeof(struct dma_desc));
		stmmac_set_rx_tail_ptr(priv, priv->ioaddr,
				       rx_q->rx_tail_addr, chan);
	}

	/* DMA TX Channel Configuration */
	for (chan = 0; chan < tx_channels_count; chan++) {
		tx_q = &priv->tx_queue[chan];

		stmmac_init_tx_chan(priv, priv->ioaddr, priv->plat->dma_cfg,
				    tx_q->dma_tx_phy, chan);

		tx_q->tx_tail_addr = tx_q->dma_tx_phy;
		stmmac_set_tx_tail_ptr(priv, priv->ioaddr,
				       tx_q->tx_tail_addr, chan);
	}

	return ret;
}