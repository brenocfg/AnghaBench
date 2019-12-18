#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_7__ {TYPE_1__* dma_ops; } ;
typedef  TYPE_2__ ide_hwif_t ;
struct TYPE_8__ {TYPE_2__* hwif; } ;
typedef  TYPE_3__ ide_drive_t ;
struct TYPE_6__ {int (* dma_sff_read_status ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int ATA_DMA_INTR ; 
 int stub1 (TYPE_2__*) ; 

int ide_dma_test_irq(ide_drive_t *drive)
{
	ide_hwif_t *hwif = drive->hwif;
	u8 dma_stat = hwif->dma_ops->dma_sff_read_status(hwif);

	return (dma_stat & ATA_DMA_INTR) ? 1 : 0;
}