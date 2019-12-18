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
typedef  int u32 ;
struct kvaser_pciefd {scalar_t__ reg_base; TYPE_1__* pci; int /*<<< orphan*/ * dma_data; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int KVASER_PCIEFD_DMA_COUNT ; 
 int KVASER_PCIEFD_DMA_MAP_BASE ; 
 int /*<<< orphan*/  KVASER_PCIEFD_DMA_SIZE ; 
 int KVASER_PCIEFD_SRB_CMD_FOR ; 
 int KVASER_PCIEFD_SRB_CMD_RDB0 ; 
 int KVASER_PCIEFD_SRB_CMD_RDB1 ; 
 scalar_t__ KVASER_PCIEFD_SRB_CMD_REG ; 
 int KVASER_PCIEFD_SRB_CTRL_DMA_ENABLE ; 
 scalar_t__ KVASER_PCIEFD_SRB_CTRL_REG ; 
 int KVASER_PCIEFD_SRB_STAT_DI ; 
 scalar_t__ KVASER_PCIEFD_SRB_STAT_REG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dmam_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  kvaser_pciefd_write_dma_map (struct kvaser_pciefd*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int kvaser_pciefd_setup_dma(struct kvaser_pciefd *pcie)
{
	int i;
	u32 srb_status;
	dma_addr_t dma_addr[KVASER_PCIEFD_DMA_COUNT];

	/* Disable the DMA */
	iowrite32(0, pcie->reg_base + KVASER_PCIEFD_SRB_CTRL_REG);
	for (i = 0; i < KVASER_PCIEFD_DMA_COUNT; i++) {
		unsigned int offset = KVASER_PCIEFD_DMA_MAP_BASE + 8 * i;

		pcie->dma_data[i] =
			dmam_alloc_coherent(&pcie->pci->dev,
					    KVASER_PCIEFD_DMA_SIZE,
					    &dma_addr[i],
					    GFP_KERNEL);

		if (!pcie->dma_data[i] || !dma_addr[i]) {
			dev_err(&pcie->pci->dev, "Rx dma_alloc(%u) failure\n",
				KVASER_PCIEFD_DMA_SIZE);
			return -ENOMEM;
		}

		kvaser_pciefd_write_dma_map(pcie, dma_addr[i], offset);
	}

	/* Reset Rx FIFO, and both DMA buffers */
	iowrite32(KVASER_PCIEFD_SRB_CMD_FOR | KVASER_PCIEFD_SRB_CMD_RDB0 |
		  KVASER_PCIEFD_SRB_CMD_RDB1,
		  pcie->reg_base + KVASER_PCIEFD_SRB_CMD_REG);

	srb_status = ioread32(pcie->reg_base + KVASER_PCIEFD_SRB_STAT_REG);
	if (!(srb_status & KVASER_PCIEFD_SRB_STAT_DI)) {
		dev_err(&pcie->pci->dev, "DMA not idle before enabling\n");
		return -EIO;
	}

	/* Enable the DMA */
	iowrite32(KVASER_PCIEFD_SRB_CTRL_DMA_ENABLE,
		  pcie->reg_base + KVASER_PCIEFD_SRB_CTRL_REG);

	return 0;
}