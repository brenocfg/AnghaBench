#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {scalar_t__ dma_base; } ;
typedef  TYPE_1__ ide_hwif_t ;
struct TYPE_5__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;

/* Variables and functions */
 scalar_t__ ATA_DMA_CMD ; 
 scalar_t__ ATA_DMA_STATUS ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int cmd646_1_dma_end(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	u8 dma_stat = 0, dma_cmd = 0;

	/* get DMA status */
	dma_stat = inb(hwif->dma_base + ATA_DMA_STATUS);
	/* read DMA command state */
	dma_cmd = inb(hwif->dma_base + ATA_DMA_CMD);
	/* stop DMA */
	outb(dma_cmd & ~1, hwif->dma_base + ATA_DMA_CMD);
	/* clear the INTR & ERROR bits */
	outb(dma_stat | 6, hwif->dma_base + ATA_DMA_STATUS);
	/* verify good DMA status */
	return (dma_stat & 7) != 4;
}