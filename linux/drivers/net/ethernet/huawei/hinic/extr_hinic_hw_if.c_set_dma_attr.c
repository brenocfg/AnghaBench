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
typedef  int u8 ;
typedef  int u32 ;
struct hinic_hwif {int dummy; } ;
typedef  enum hinic_pcie_tph { ____Placeholder_hinic_pcie_tph } hinic_pcie_tph ;
typedef  enum hinic_pcie_nosnoop { ____Placeholder_hinic_pcie_nosnoop } hinic_pcie_nosnoop ;

/* Variables and functions */
 int /*<<< orphan*/  AT ; 
 int HINIC_CSR_DMA_ATTR_ADDR (int) ; 
 int HINIC_DMA_ATTR_CLEAR (int,int /*<<< orphan*/ ) ; 
 int HINIC_DMA_ATTR_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_SNOOPING ; 
 int /*<<< orphan*/  PH ; 
 int /*<<< orphan*/  ST ; 
 int /*<<< orphan*/  TPH_EN ; 
 int hinic_hwif_read_reg (struct hinic_hwif*,int) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (struct hinic_hwif*,int,int) ; 

__attribute__((used)) static void set_dma_attr(struct hinic_hwif *hwif, u32 entry_idx,
			 u8 st, u8 at, u8 ph,
			 enum hinic_pcie_nosnoop no_snooping,
			 enum hinic_pcie_tph tph_en)
{
	u32 addr, val, dma_attr_entry;

	/* Read Modify Write */
	addr = HINIC_CSR_DMA_ATTR_ADDR(entry_idx);

	val = hinic_hwif_read_reg(hwif, addr);
	val = HINIC_DMA_ATTR_CLEAR(val, ST)             &
	      HINIC_DMA_ATTR_CLEAR(val, AT)             &
	      HINIC_DMA_ATTR_CLEAR(val, PH)             &
	      HINIC_DMA_ATTR_CLEAR(val, NO_SNOOPING)    &
	      HINIC_DMA_ATTR_CLEAR(val, TPH_EN);

	dma_attr_entry = HINIC_DMA_ATTR_SET(st, ST)                     |
			 HINIC_DMA_ATTR_SET(at, AT)                     |
			 HINIC_DMA_ATTR_SET(ph, PH)                     |
			 HINIC_DMA_ATTR_SET(no_snooping, NO_SNOOPING)   |
			 HINIC_DMA_ATTR_SET(tph_en, TPH_EN);

	val |= dma_attr_entry;
	hinic_hwif_write_reg(hwif, addr, val);
}