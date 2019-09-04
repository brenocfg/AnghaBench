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
struct ata_queued_cmd {struct ata_device* dev; struct ata_port* ap; } ;
struct ata_port {struct ata_device* private_data; } ;
struct ata_device {int dummy; } ;

/* Variables and functions */
 unsigned int ata_bmdma_qc_issue (struct ata_queued_cmd*) ; 
 scalar_t__ ata_dma_enabled (struct ata_device*) ; 
 scalar_t__ ata_using_udma (struct ata_device*) ; 
 int /*<<< orphan*/  sc1200_set_dmamode (struct ata_port*,struct ata_device*) ; 

__attribute__((used)) static unsigned int sc1200_qc_issue(struct ata_queued_cmd *qc)
{
	struct ata_port *ap = qc->ap;
	struct ata_device *adev = qc->dev;
	struct ata_device *prev = ap->private_data;

	/* See if the DMA settings could be wrong */
	if (ata_dma_enabled(adev) && adev != prev && prev != NULL) {
		/* Maybe, but do the channels match MWDMA/UDMA ? */
		if ((ata_using_udma(adev) && !ata_using_udma(prev)) ||
		    (ata_using_udma(prev) && !ata_using_udma(adev)))
		    	/* Switch the mode bits */
		    	sc1200_set_dmamode(ap, adev);
	}

	return ata_bmdma_qc_issue(qc);
}