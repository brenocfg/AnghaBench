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
struct esp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CSR ; 
 int DMA_INT_ENAB ; 
 int DMA_RST_SCSI ; 
 int dma_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_write32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sun3x_esp_reset_dma(struct esp *esp)
{
	u32 val;

	val = dma_read32(DMA_CSR);
	dma_write32(val | DMA_RST_SCSI, DMA_CSR);
	dma_write32(val & ~DMA_RST_SCSI, DMA_CSR);

	/* Enable interrupts.  */
	val = dma_read32(DMA_CSR);
	dma_write32(val | DMA_INT_ENAB, DMA_CSR);
}