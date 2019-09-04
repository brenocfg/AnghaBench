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
struct sprd_dma_chn {scalar_t__ chn_base; } ;
typedef  enum sprd_dma_req_mode { ____Placeholder_sprd_dma_req_mode } sprd_dma_req_mode ;

/* Variables and functions */
 scalar_t__ SPRD_DMA_CHN_FRG_LEN ; 
 int SPRD_DMA_REQ_MODE_MASK ; 
 int SPRD_DMA_REQ_MODE_OFFSET ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static enum sprd_dma_req_mode sprd_dma_get_req_type(struct sprd_dma_chn *schan)
{
	u32 frag_reg = readl(schan->chn_base + SPRD_DMA_CHN_FRG_LEN);

	return (frag_reg >> SPRD_DMA_REQ_MODE_OFFSET) & SPRD_DMA_REQ_MODE_MASK;
}