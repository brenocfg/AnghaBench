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
struct plat_stmmacenet_data {int clk_csr; int has_gmac4; int tso_en; int rx_queues_to_use; int tx_queues_to_use; int tx_fifo_size; int rx_fifo_size; int unicast_filter_entries; int /*<<< orphan*/  maxmtu; int /*<<< orphan*/  multicast_filter_bins; int /*<<< orphan*/ * stmmac_clk; int /*<<< orphan*/  clk_ptp_rate; int /*<<< orphan*/  ptp_max_adj; TYPE_5__* axi; TYPE_4__* dma_cfg; TYPE_3__* mdio_bus_data; TYPE_2__* tx_queues_cfg; int /*<<< orphan*/  tx_sched_algorithm; TYPE_1__* rx_queues_cfg; int /*<<< orphan*/  rx_sched_algorithm; scalar_t__ force_sf_dma_mode; scalar_t__ has_gmac; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int axi_wr_osr_lmt; int axi_rd_osr_lmt; int* axi_blen; scalar_t__ axi_xit_frm; scalar_t__ axi_lpi_en; } ;
struct TYPE_9__ {int pbl; int pblx8; scalar_t__ aal; scalar_t__ mixed_burst; scalar_t__ fixed_burst; } ;
struct TYPE_8__ {scalar_t__ phy_mask; } ;
struct TYPE_7__ {int use_prio; int weight; void* mode_to_use; } ;
struct TYPE_6__ {int chan; int use_prio; int pkt_route; void* mode_to_use; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HASH_TABLE_SIZE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JUMBO_LEN ; 
 void* MTL_QUEUE_DCB ; 
 int /*<<< orphan*/  MTL_RX_ALGORITHM_SP ; 
 int /*<<< orphan*/  MTL_TX_ALGORITHM_WRR ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clk_register_fixed_rate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 TYPE_5__* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_mgbe_common_data(struct pci_dev *pdev,
				  struct plat_stmmacenet_data *plat)
{
	int i;

	plat->clk_csr = 5;
	plat->has_gmac = 0;
	plat->has_gmac4 = 1;
	plat->force_sf_dma_mode = 0;
	plat->tso_en = 1;

	plat->rx_sched_algorithm = MTL_RX_ALGORITHM_SP;

	for (i = 0; i < plat->rx_queues_to_use; i++) {
		plat->rx_queues_cfg[i].mode_to_use = MTL_QUEUE_DCB;
		plat->rx_queues_cfg[i].chan = i;

		/* Disable Priority config by default */
		plat->rx_queues_cfg[i].use_prio = false;

		/* Disable RX queues routing by default */
		plat->rx_queues_cfg[i].pkt_route = 0x0;
	}

	for (i = 0; i < plat->tx_queues_to_use; i++) {
		plat->tx_queues_cfg[i].mode_to_use = MTL_QUEUE_DCB;

		/* Disable Priority config by default */
		plat->tx_queues_cfg[i].use_prio = false;
	}

	/* FIFO size is 4096 bytes for 1 tx/rx queue */
	plat->tx_fifo_size = plat->tx_queues_to_use * 4096;
	plat->rx_fifo_size = plat->rx_queues_to_use * 4096;

	plat->tx_sched_algorithm = MTL_TX_ALGORITHM_WRR;
	plat->tx_queues_cfg[0].weight = 0x09;
	plat->tx_queues_cfg[1].weight = 0x0A;
	plat->tx_queues_cfg[2].weight = 0x0B;
	plat->tx_queues_cfg[3].weight = 0x0C;
	plat->tx_queues_cfg[4].weight = 0x0D;
	plat->tx_queues_cfg[5].weight = 0x0E;
	plat->tx_queues_cfg[6].weight = 0x0F;
	plat->tx_queues_cfg[7].weight = 0x10;

	plat->mdio_bus_data->phy_mask = 0;

	plat->dma_cfg->pbl = 32;
	plat->dma_cfg->pblx8 = true;
	plat->dma_cfg->fixed_burst = 0;
	plat->dma_cfg->mixed_burst = 0;
	plat->dma_cfg->aal = 0;

	plat->axi = devm_kzalloc(&pdev->dev, sizeof(*plat->axi),
				 GFP_KERNEL);
	if (!plat->axi)
		return -ENOMEM;

	plat->axi->axi_lpi_en = 0;
	plat->axi->axi_xit_frm = 0;
	plat->axi->axi_wr_osr_lmt = 1;
	plat->axi->axi_rd_osr_lmt = 1;
	plat->axi->axi_blen[0] = 4;
	plat->axi->axi_blen[1] = 8;
	plat->axi->axi_blen[2] = 16;

	plat->ptp_max_adj = plat->clk_ptp_rate;

	/* Set system clock */
	plat->stmmac_clk = clk_register_fixed_rate(&pdev->dev,
						   "stmmac-clk", NULL, 0,
						   plat->clk_ptp_rate);

	if (IS_ERR(plat->stmmac_clk)) {
		dev_warn(&pdev->dev, "Fail to register stmmac-clk\n");
		plat->stmmac_clk = NULL;
	}
	clk_prepare_enable(plat->stmmac_clk);

	/* Set default value for multicast hash bins */
	plat->multicast_filter_bins = HASH_TABLE_SIZE;

	/* Set default value for unicast filter entries */
	plat->unicast_filter_entries = 1;

	/* Set the maxmtu to a default of JUMBO_LEN */
	plat->maxmtu = JUMBO_LEN;

	return 0;
}