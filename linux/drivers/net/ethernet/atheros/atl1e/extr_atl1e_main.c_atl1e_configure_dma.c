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
typedef  int u32 ;
struct atl1e_hw {scalar_t__ dmaw_dly_cnt; scalar_t__ dmar_dly_cnt; scalar_t__ dmaw_block; scalar_t__ dmar_block; } ;
struct atl1e_adapter {struct atl1e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_WRITE_REG (struct atl1e_hw*,int /*<<< orphan*/ ,int) ; 
 int DMA_CTRL_DMAR_BURST_LEN_MASK ; 
 int DMA_CTRL_DMAR_BURST_LEN_SHIFT ; 
 int DMA_CTRL_DMAR_DLY_CNT_MASK ; 
 int DMA_CTRL_DMAR_DLY_CNT_SHIFT ; 
 int DMA_CTRL_DMAR_OUT_ORDER ; 
 int DMA_CTRL_DMAR_REQ_PRI ; 
 int DMA_CTRL_DMAW_BURST_LEN_MASK ; 
 int DMA_CTRL_DMAW_BURST_LEN_SHIFT ; 
 int DMA_CTRL_DMAW_DLY_CNT_MASK ; 
 int DMA_CTRL_DMAW_DLY_CNT_SHIFT ; 
 int DMA_CTRL_RXCMB_EN ; 
 int /*<<< orphan*/  REG_DMA_CTRL ; 

__attribute__((used)) static inline void atl1e_configure_dma(struct atl1e_adapter *adapter)
{
	struct atl1e_hw *hw = &adapter->hw;
	u32 dma_ctrl_data = 0;

	dma_ctrl_data = DMA_CTRL_RXCMB_EN;
	dma_ctrl_data |= (((u32)hw->dmar_block) & DMA_CTRL_DMAR_BURST_LEN_MASK)
		<< DMA_CTRL_DMAR_BURST_LEN_SHIFT;
	dma_ctrl_data |= (((u32)hw->dmaw_block) & DMA_CTRL_DMAW_BURST_LEN_MASK)
		<< DMA_CTRL_DMAW_BURST_LEN_SHIFT;
	dma_ctrl_data |= DMA_CTRL_DMAR_REQ_PRI | DMA_CTRL_DMAR_OUT_ORDER;
	dma_ctrl_data |= (((u32)hw->dmar_dly_cnt) & DMA_CTRL_DMAR_DLY_CNT_MASK)
		<< DMA_CTRL_DMAR_DLY_CNT_SHIFT;
	dma_ctrl_data |= (((u32)hw->dmaw_dly_cnt) & DMA_CTRL_DMAW_DLY_CNT_MASK)
		<< DMA_CTRL_DMAW_DLY_CNT_SHIFT;

	AT_WRITE_REG(hw, REG_DMA_CTRL, dma_ctrl_data);
}