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
struct TYPE_2__ {unsigned short csr; int dma_count_hi; int dma_count_lo; int fifo_count_hi; int fifo_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDC_CHN_START ; 
 int /*<<< orphan*/  UDC_CSR ; 
 TYPE_1__* dregs ; 
 int sun3_dma_orig_count ; 
 int /*<<< orphan*/  sun3_udc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int sun3scsi_dma_start(unsigned long count, unsigned char *data)
{
#ifdef SUN3_SCSI_VME
	unsigned short csr;

	csr = dregs->csr;

	dregs->dma_count_hi = (sun3_dma_orig_count >> 16);
	dregs->dma_count_lo = (sun3_dma_orig_count & 0xffff);

	dregs->fifo_count_hi = (sun3_dma_orig_count >> 16);
	dregs->fifo_count = (sun3_dma_orig_count & 0xffff);

/*	if(!(csr & CSR_DMA_ENABLE))
 *		dregs->csr |= CSR_DMA_ENABLE;
 */
#else
    sun3_udc_write(UDC_CHN_START, UDC_CSR);
#endif
    
    return 0;
}