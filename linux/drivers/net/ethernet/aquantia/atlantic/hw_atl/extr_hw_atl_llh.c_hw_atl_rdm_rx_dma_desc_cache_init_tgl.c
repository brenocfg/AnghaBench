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
struct aq_hw_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_ADR ; 
 int /*<<< orphan*/  HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_MSK ; 
 int /*<<< orphan*/  HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_SHIFT ; 
 int aq_hw_read_reg_bit (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aq_hw_write_reg_bit (struct aq_hw_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void hw_atl_rdm_rx_dma_desc_cache_init_tgl(struct aq_hw_s *aq_hw)
{
	u32 val;

	val = aq_hw_read_reg_bit(aq_hw, HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_ADR,
				 HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_MSK,
				 HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_SHIFT);

	aq_hw_write_reg_bit(aq_hw, HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_ADR,
			    HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_MSK,
			    HW_ATL_RDM_RX_DMA_DESC_CACHE_INIT_SHIFT,
			    val ^ 1);
}