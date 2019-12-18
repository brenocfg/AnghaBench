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
struct TYPE_2__ {int /*<<< orphan*/  fragmens_len; int /*<<< orphan*/  width; struct dma_chan** dma_chan; } ;
struct sprd_spi {TYPE_1__ dma; int /*<<< orphan*/  phy_base; } ;
struct spi_transfer {int len; int /*<<< orphan*/  tx_sg; } ;
struct dma_slave_config {int /*<<< orphan*/  src_maxburst; int /*<<< orphan*/  dst_addr_width; int /*<<< orphan*/  src_addr_width; int /*<<< orphan*/  dst_addr; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 size_t SPRD_SPI_TX ; 
 int sprd_spi_dma_submit (struct dma_chan*,struct dma_slave_config*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sprd_spi_dma_tx_config(struct sprd_spi *ss, struct spi_transfer *t)
{
	struct dma_chan *dma_chan = ss->dma.dma_chan[SPRD_SPI_TX];
	struct dma_slave_config config = {
		.dst_addr = ss->phy_base,
		.src_addr_width = ss->dma.width,
		.dst_addr_width = ss->dma.width,
		.src_maxburst = ss->dma.fragmens_len,
	};
	int ret;

	ret = sprd_spi_dma_submit(dma_chan, &config, &t->tx_sg, DMA_MEM_TO_DEV);
	if (ret)
		return ret;

	return t->len;
}