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
struct tegra_dma_channel {int dummy; } ;
typedef  enum dma_slave_buswidth { ____Placeholder_dma_slave_buswidth } dma_slave_buswidth ;

/* Variables and functions */
#define  DMA_SLAVE_BUSWIDTH_1_BYTE 131 
#define  DMA_SLAVE_BUSWIDTH_2_BYTES 130 
#define  DMA_SLAVE_BUSWIDTH_4_BYTES 129 
#define  DMA_SLAVE_BUSWIDTH_8_BYTES 128 
 int TEGRA_APBDMA_APBSEQ_BUS_WIDTH_16 ; 
 int TEGRA_APBDMA_APBSEQ_BUS_WIDTH_32 ; 
 int TEGRA_APBDMA_APBSEQ_BUS_WIDTH_64 ; 
 int TEGRA_APBDMA_APBSEQ_BUS_WIDTH_8 ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tdc2dev (struct tegra_dma_channel*) ; 

__attribute__((used)) static inline int get_bus_width(struct tegra_dma_channel *tdc,
		enum dma_slave_buswidth slave_bw)
{
	switch (slave_bw) {
	case DMA_SLAVE_BUSWIDTH_1_BYTE:
		return TEGRA_APBDMA_APBSEQ_BUS_WIDTH_8;
	case DMA_SLAVE_BUSWIDTH_2_BYTES:
		return TEGRA_APBDMA_APBSEQ_BUS_WIDTH_16;
	case DMA_SLAVE_BUSWIDTH_4_BYTES:
		return TEGRA_APBDMA_APBSEQ_BUS_WIDTH_32;
	case DMA_SLAVE_BUSWIDTH_8_BYTES:
		return TEGRA_APBDMA_APBSEQ_BUS_WIDTH_64;
	default:
		dev_warn(tdc2dev(tdc),
			"slave bw is not supported, using 32bits\n");
		return TEGRA_APBDMA_APBSEQ_BUS_WIDTH_32;
	}
}