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
typedef  void* u32 ;
struct stm32_spi {int cur_bpw; int cur_fthlv; int /*<<< orphan*/  dev; TYPE_4__* cfg; scalar_t__ phys_addr; } ;
struct dma_slave_config {int direction; int src_addr_width; int dst_addr_width; void* dst_maxburst; scalar_t__ dst_addr; void* src_maxburst; scalar_t__ src_addr; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;
struct TYPE_8__ {TYPE_3__* regs; scalar_t__ has_fifo; } ;
struct TYPE_6__ {scalar_t__ reg; } ;
struct TYPE_5__ {scalar_t__ reg; } ;
struct TYPE_7__ {TYPE_2__ tx; TYPE_1__ rx; } ;

/* Variables and functions */
 scalar_t__ DMA_DEV_TO_MEM ; 
 scalar_t__ DMA_MEM_TO_DEV ; 
 int DMA_SLAVE_BUSWIDTH_1_BYTE ; 
 int DMA_SLAVE_BUSWIDTH_2_BYTES ; 
 int DMA_SLAVE_BUSWIDTH_4_BYTES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,void*) ; 
 int /*<<< orphan*/  memset (struct dma_slave_config*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void stm32_spi_dma_config(struct stm32_spi *spi,
				 struct dma_slave_config *dma_conf,
				 enum dma_transfer_direction dir)
{
	enum dma_slave_buswidth buswidth;
	u32 maxburst;

	if (spi->cur_bpw <= 8)
		buswidth = DMA_SLAVE_BUSWIDTH_1_BYTE;
	else if (spi->cur_bpw <= 16)
		buswidth = DMA_SLAVE_BUSWIDTH_2_BYTES;
	else
		buswidth = DMA_SLAVE_BUSWIDTH_4_BYTES;

	if (spi->cfg->has_fifo) {
		/* Valid for DMA Half or Full Fifo threshold */
		if (spi->cur_fthlv == 2)
			maxburst = 1;
		else
			maxburst = spi->cur_fthlv;
	} else {
		maxburst = 1;
	}

	memset(dma_conf, 0, sizeof(struct dma_slave_config));
	dma_conf->direction = dir;
	if (dma_conf->direction == DMA_DEV_TO_MEM) { /* RX */
		dma_conf->src_addr = spi->phys_addr + spi->cfg->regs->rx.reg;
		dma_conf->src_addr_width = buswidth;
		dma_conf->src_maxburst = maxburst;

		dev_dbg(spi->dev, "Rx DMA config buswidth=%d, maxburst=%d\n",
			buswidth, maxburst);
	} else if (dma_conf->direction == DMA_MEM_TO_DEV) { /* TX */
		dma_conf->dst_addr = spi->phys_addr + spi->cfg->regs->tx.reg;
		dma_conf->dst_addr_width = buswidth;
		dma_conf->dst_maxburst = maxburst;

		dev_dbg(spi->dev, "Tx DMA config buswidth=%d, maxburst=%d\n",
			buswidth, maxburst);
	}
}