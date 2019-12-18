#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct NCR5380_hostdata {int /*<<< orphan*/  host; } ;
typedef  scalar_t__ addr ;
struct TYPE_5__ {int fifo_count; unsigned long dma_addr_hi; unsigned long dma_addr_lo; int /*<<< orphan*/  csr; scalar_t__ fifo_count_hi; scalar_t__ dma_count_lo; scalar_t__ dma_count_hi; } ;
struct TYPE_4__ {unsigned long addr_hi; unsigned long addr_lo; int count; int /*<<< orphan*/  rsel; int /*<<< orphan*/  mode_lo; int /*<<< orphan*/  mode_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_FIFO ; 
 int /*<<< orphan*/  CSR_PACK_ENABLE ; 
 int /*<<< orphan*/  CSR_SEND ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NCR5380_dprint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDEBUG_DMA ; 
 int /*<<< orphan*/  UDC_CHN_HI ; 
 int /*<<< orphan*/  UDC_CHN_LO ; 
 int /*<<< orphan*/  UDC_CSR ; 
 int UDC_INT_ENABLE ; 
 int /*<<< orphan*/  UDC_MODE ; 
 int /*<<< orphan*/  UDC_MODE_HIWORD ; 
 int /*<<< orphan*/  UDC_MODE_LRECV ; 
 int /*<<< orphan*/  UDC_MODE_LSEND ; 
 int UDC_RESET ; 
 int /*<<< orphan*/  UDC_RSEL_RECV ; 
 int /*<<< orphan*/  UDC_RSEL_SEND ; 
 TYPE_3__* dregs ; 
 scalar_t__ dvma_map (unsigned long,int) ; 
 scalar_t__ dvma_map_vme (unsigned long,int) ; 
 int /*<<< orphan*/  dvma_unmap (int /*<<< orphan*/ *) ; 
 int dvma_vtob (TYPE_1__*) ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/ * sun3_dma_orig_addr ; 
 int sun3_dma_orig_count ; 
 int /*<<< orphan*/  sun3_udc_write (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* udc_regs ; 

__attribute__((used)) static int sun3scsi_dma_setup(struct NCR5380_hostdata *hostdata,
                              unsigned char *data, int count, int write_flag)
{
	void *addr;

	if(sun3_dma_orig_addr != NULL)
		dvma_unmap(sun3_dma_orig_addr);

#ifdef SUN3_SCSI_VME
	addr = (void *)dvma_map_vme((unsigned long) data, count);
#else
	addr = (void *)dvma_map((unsigned long) data, count);
#endif
		
	sun3_dma_orig_addr = addr;
	sun3_dma_orig_count = count;

#ifndef SUN3_SCSI_VME
	dregs->fifo_count = 0;
	sun3_udc_write(UDC_RESET, UDC_CSR);
	
	/* reset fifo */
	dregs->csr &= ~CSR_FIFO;
	dregs->csr |= CSR_FIFO;
#endif
	
	/* set direction */
	if(write_flag)
		dregs->csr |= CSR_SEND;
	else
		dregs->csr &= ~CSR_SEND;
	
#ifdef SUN3_SCSI_VME
	dregs->csr |= CSR_PACK_ENABLE;

	dregs->dma_addr_hi = ((unsigned long)addr >> 16);
	dregs->dma_addr_lo = ((unsigned long)addr & 0xffff);

	dregs->dma_count_hi = 0;
	dregs->dma_count_lo = 0;
	dregs->fifo_count_hi = 0;
	dregs->fifo_count = 0;
#else
	/* byte count for fifo */
	dregs->fifo_count = count;

	sun3_udc_write(UDC_RESET, UDC_CSR);
	
	/* reset fifo */
	dregs->csr &= ~CSR_FIFO;
	dregs->csr |= CSR_FIFO;
	
	if(dregs->fifo_count != count) { 
		shost_printk(KERN_ERR, hostdata->host,
		             "FIFO mismatch %04x not %04x\n",
		             dregs->fifo_count, (unsigned int) count);
		NCR5380_dprint(NDEBUG_DMA, hostdata->host);
	}

	/* setup udc */
	udc_regs->addr_hi = (((unsigned long)(addr) & 0xff0000) >> 8);
	udc_regs->addr_lo = ((unsigned long)(addr) & 0xffff);
	udc_regs->count = count/2; /* count in words */
	udc_regs->mode_hi = UDC_MODE_HIWORD;
	if(write_flag) {
		if(count & 1)
			udc_regs->count++;
		udc_regs->mode_lo = UDC_MODE_LSEND;
		udc_regs->rsel = UDC_RSEL_SEND;
	} else {
		udc_regs->mode_lo = UDC_MODE_LRECV;
		udc_regs->rsel = UDC_RSEL_RECV;
	}
	
	/* announce location of regs block */
	sun3_udc_write(((dvma_vtob(udc_regs) & 0xff0000) >> 8),
		       UDC_CHN_HI); 

	sun3_udc_write((dvma_vtob(udc_regs) & 0xffff), UDC_CHN_LO);

	/* set dma master on */
	sun3_udc_write(0xd, UDC_MODE);

	/* interrupt enable */
	sun3_udc_write(UDC_INT_ENABLE, UDC_CSR);
#endif
	
       	return count;

}