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
typedef  int /*<<< orphan*/  u32 ;
struct xgene_dma {scalar_t__ csr_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  XGENE_DMA_CH_SETUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGENE_DMA_ENABLE (int /*<<< orphan*/ ) ; 
 scalar_t__ XGENE_DMA_GCR ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void xgene_dma_enable(struct xgene_dma *pdma)
{
	u32 val;

	/* Configure and enable DMA engine */
	val = ioread32(pdma->csr_dma + XGENE_DMA_GCR);
	XGENE_DMA_CH_SETUP(val);
	XGENE_DMA_ENABLE(val);
	iowrite32(val, pdma->csr_dma + XGENE_DMA_GCR);
}