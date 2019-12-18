#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pch_gbe_hw {TYPE_2__* reg; } ;
struct pch_gbe_adapter {TYPE_1__* tx_ring; int /*<<< orphan*/  netdev; struct pch_gbe_hw hw; } ;
struct TYPE_4__ {int /*<<< orphan*/  DMA_CTRL; int /*<<< orphan*/  TX_DSC_SW_P; int /*<<< orphan*/  TX_DSC_SIZE; int /*<<< orphan*/  TX_DSC_BASE; } ;
struct TYPE_3__ {scalar_t__ size; scalar_t__ dma; } ;

/* Variables and functions */
 scalar_t__ PCH_GBE_TX_DMA_EN ; 
 scalar_t__ ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,unsigned long long,scalar_t__) ; 

__attribute__((used)) static void pch_gbe_configure_tx(struct pch_gbe_adapter *adapter)
{
	struct pch_gbe_hw *hw = &adapter->hw;
	u32 tdba, tdlen, dctrl;

	netdev_dbg(adapter->netdev, "dma addr = 0x%08llx  size = 0x%08x\n",
		   (unsigned long long)adapter->tx_ring->dma,
		   adapter->tx_ring->size);

	/* Setup the HW Tx Head and Tail descriptor pointers */
	tdba = adapter->tx_ring->dma;
	tdlen = adapter->tx_ring->size - 0x10;
	iowrite32(tdba, &hw->reg->TX_DSC_BASE);
	iowrite32(tdlen, &hw->reg->TX_DSC_SIZE);
	iowrite32(tdba, &hw->reg->TX_DSC_SW_P);

	/* Enables Transmission DMA */
	dctrl = ioread32(&hw->reg->DMA_CTRL);
	dctrl |= PCH_GBE_TX_DMA_EN;
	iowrite32(dctrl, &hw->reg->DMA_CTRL);
}