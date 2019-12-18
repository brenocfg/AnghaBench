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
typedef  int u16 ;
struct atl1e_tx_ring {int dma; int cmb_dma; scalar_t__ count; } ;
struct atl1e_rx_ring {int page_size; struct atl1e_rx_page_desc* rx_page_desc; } ;
struct atl1e_rx_page_desc {TYPE_1__* rx_page; } ;
struct atl1e_hw {int dummy; } ;
struct atl1e_adapter {int ring_dma; struct atl1e_tx_ring tx_ring; struct atl1e_rx_ring rx_ring; struct atl1e_hw hw; } ;
struct TYPE_2__ {int dma; int write_offset_dma; } ;

/* Variables and functions */
 int AT_DMA_HI_ADDR_MASK ; 
 int AT_DMA_LO_ADDR_MASK ; 
 int AT_MAX_RECEIVE_QUEUE ; 
 int AT_PAGE_NUM_PER_QUEUE ; 
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AT_WRITE_REGB (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_DESC_BASE_ADDR_HI ; 
 int /*<<< orphan*/  REG_HOST_RXFPAGE_SIZE ; 
 int /*<<< orphan*/  REG_HOST_TX_CMB_LO ; 
 int /*<<< orphan*/  REG_LOAD_PTR ; 
 int /*<<< orphan*/  REG_TPD_BASE_ADDR_LO ; 
 int /*<<< orphan*/  REG_TPD_RING_SIZE ; 
 int /*<<< orphan*/ * atl1e_rx_page_hi_addr_regs ; 
 int /*<<< orphan*/ ** atl1e_rx_page_lo_addr_regs ; 
 int /*<<< orphan*/ ** atl1e_rx_page_vld_regs ; 
 int /*<<< orphan*/ ** atl1e_rx_page_write_offset_regs ; 

__attribute__((used)) static inline void atl1e_configure_des_ring(struct atl1e_adapter *adapter)
{

	struct atl1e_hw *hw = &adapter->hw;
	struct atl1e_rx_ring *rx_ring = &adapter->rx_ring;
	struct atl1e_tx_ring *tx_ring = &adapter->tx_ring;
	struct atl1e_rx_page_desc *rx_page_desc = NULL;
	int i, j;

	AT_WRITE_REG(hw, REG_DESC_BASE_ADDR_HI,
			(u32)((adapter->ring_dma & AT_DMA_HI_ADDR_MASK) >> 32));
	AT_WRITE_REG(hw, REG_TPD_BASE_ADDR_LO,
			(u32)((tx_ring->dma) & AT_DMA_LO_ADDR_MASK));
	AT_WRITE_REG(hw, REG_TPD_RING_SIZE, (u16)(tx_ring->count));
	AT_WRITE_REG(hw, REG_HOST_TX_CMB_LO,
			(u32)((tx_ring->cmb_dma) & AT_DMA_LO_ADDR_MASK));

	rx_page_desc = rx_ring->rx_page_desc;
	/* RXF Page Physical address / Page Length */
	for (i = 0; i < AT_MAX_RECEIVE_QUEUE; i++) {
		AT_WRITE_REG(hw, atl1e_rx_page_hi_addr_regs[i],
				 (u32)((adapter->ring_dma &
				 AT_DMA_HI_ADDR_MASK) >> 32));
		for (j = 0; j < AT_PAGE_NUM_PER_QUEUE; j++) {
			u32 page_phy_addr;
			u32 offset_phy_addr;

			page_phy_addr = rx_page_desc[i].rx_page[j].dma;
			offset_phy_addr =
				   rx_page_desc[i].rx_page[j].write_offset_dma;

			AT_WRITE_REG(hw, atl1e_rx_page_lo_addr_regs[i][j],
					page_phy_addr & AT_DMA_LO_ADDR_MASK);
			AT_WRITE_REG(hw, atl1e_rx_page_write_offset_regs[i][j],
					offset_phy_addr & AT_DMA_LO_ADDR_MASK);
			AT_WRITE_REGB(hw, atl1e_rx_page_vld_regs[i][j], 1);
		}
	}
	/* Page Length */
	AT_WRITE_REG(hw, REG_HOST_RXFPAGE_SIZE, rx_ring->page_size);
	/* Load all of base address above */
	AT_WRITE_REG(hw, REG_LOAD_PTR, 1);
}