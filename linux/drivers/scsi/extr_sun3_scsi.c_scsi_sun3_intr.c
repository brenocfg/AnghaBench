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
struct Scsi_Host {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {unsigned short csr; } ;

/* Variables and functions */
 unsigned short CSR_DMA_BUSERR ; 
 unsigned short CSR_DMA_CONFLICT ; 
 unsigned short CSR_DMA_ENABLE ; 
 unsigned short CSR_DMA_INT ; 
 unsigned short CSR_GOOD ; 
 unsigned short CSR_SDB_INT ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  NCR5380_intr (int,void*) ; 
 TYPE_1__* dregs ; 
 int /*<<< orphan*/  shost_printk (int /*<<< orphan*/ ,struct Scsi_Host*,char*) ; 

__attribute__((used)) static irqreturn_t scsi_sun3_intr(int irq, void *dev)
{
	struct Scsi_Host *instance = dev;
	unsigned short csr = dregs->csr;
	int handled = 0;

#ifdef SUN3_SCSI_VME
	dregs->csr &= ~CSR_DMA_ENABLE;
#endif

	if(csr & ~CSR_GOOD) {
		if (csr & CSR_DMA_BUSERR)
			shost_printk(KERN_ERR, instance, "bus error in DMA\n");
		if (csr & CSR_DMA_CONFLICT)
			shost_printk(KERN_ERR, instance, "DMA conflict\n");
		handled = 1;
	}

	if(csr & (CSR_SDB_INT | CSR_DMA_INT)) {
		NCR5380_intr(irq, dev);
		handled = 1;
	}

	return IRQ_RETVAL(handled);
}