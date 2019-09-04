#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_6__ {int host_flags; } ;

/* Variables and functions */
 int IDE_HFLAG_MMIO ; 
 int ide_dma_test_irq (TYPE_2__*) ; 
 int siimage_mmio_dma_test_irq (TYPE_2__*) ; 

__attribute__((used)) static int siimage_dma_test_irq(ide_drive_t *drive)
{
	if (drive->hwif->host_flags & IDE_HFLAG_MMIO)
		return siimage_mmio_dma_test_irq(drive);
	else
		return ide_dma_test_irq(drive);
}