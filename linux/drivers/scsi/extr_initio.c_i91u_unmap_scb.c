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
struct sg_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_handle; int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {TYPE_1__ SCp; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int SENSE_SIZE ; 
 int TOTAL_SG_ENTRY ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_dma_unmap (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sg_count (struct scsi_cmnd*) ; 

__attribute__((used)) static void i91u_unmap_scb(struct pci_dev *pci_dev, struct scsi_cmnd *cmnd)
{
	/* auto sense buffer */
	if (cmnd->SCp.ptr) {
		dma_unmap_single(&pci_dev->dev,
				 (dma_addr_t)((unsigned long)cmnd->SCp.ptr),
				 SENSE_SIZE, DMA_FROM_DEVICE);
		cmnd->SCp.ptr = NULL;
	}

	/* request buffer */
	if (scsi_sg_count(cmnd)) {
		dma_unmap_single(&pci_dev->dev, cmnd->SCp.dma_handle,
				 sizeof(struct sg_entry) * TOTAL_SG_ENTRY,
				 DMA_BIDIRECTIONAL);

		scsi_dma_unmap(cmnd);
	}
}