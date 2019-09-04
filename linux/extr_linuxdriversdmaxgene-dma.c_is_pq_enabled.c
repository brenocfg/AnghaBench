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
struct xgene_dma {scalar_t__ csr_efuse; } ;

/* Variables and functions */
 int XGENE_DMA_PQ_DISABLE_MASK ; 
 scalar_t__ XGENE_SOC_JTAG1_SHADOW ; 
 int ioread32 (scalar_t__) ; 

__attribute__((used)) static bool is_pq_enabled(struct xgene_dma *pdma)
{
	u32 val;

	val = ioread32(pdma->csr_efuse + XGENE_SOC_JTAG1_SHADOW);
	return !(val & XGENE_DMA_PQ_DISABLE_MASK);
}